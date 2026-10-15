#!/usr/bin/env python3
"""Maintain C/C++ source URLs and prepare isolated PDF sources."""

import argparse
import codecs
import re
import shutil
import subprocess
import sys
from pathlib import Path
from urllib.parse import quote

ROOT = Path(__file__).resolve().parent.parent
BASE_URL = "https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/"
SOURCE_EXTENSIONS = {".cpp", ".cc", ".cxx", ".c", ".h", ".hh", ".hpp", ".hxx", ".ipp", ".tpp"}

MANAGED_SOURCE = re.compile(
    rb"^/\* https://github\.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/[^\r\n ]+ \*/(?:\r?\n)?$"
)


def is_source(path):
    return Path(path).suffix in SOURCE_EXTENSIONS


def source_url(path):
    return BASE_URL + quote(path, safe="/")


def expected_header(path):
    if not is_source(path):
        raise ValueError(f"{path}: not a supported C/C++ source file")
    return f"/* {source_url(path)} */".encode("utf-8")


def split_content(data):
    bom = codecs.BOM_UTF8 if data.startswith(codecs.BOM_UTF8) else b""
    return bom, data[len(bom):].splitlines(keepends=True)


def managed_prefix(lines):
    end = 0
    while end < len(lines):
        line = lines[end]
        if not MANAGED_SOURCE.fullmatch(line):
            break
        end += 1
    return end


def regular_source(root, path):
    file = root / path
    parts = Path(path).parts
    if any(root.joinpath(*parts[:index]).is_symlink() for index in range(1, len(parts) + 1)):
        raise ValueError(f"{path}: symlinks in source paths are not supported")
    if root.resolve() not in file.resolve().parents or not file.is_file():
        raise ValueError(f"{path}: expected a regular file inside the repository")
    return file


def check_content(path, data):
    expected = (expected_header(path),)
    _, lines = split_content(data)
    errors = []
    for index, header in enumerate(expected):
        actual = lines[index].rstrip(b"\r\n") if index < len(lines) else b""
        if actual != header:
            errors.append(
                f"{path}:{index + 1}: expected {header.decode()!r}, "
                f"got {actual.decode('utf-8', errors='replace')!r}"
            )
    if managed_prefix(lines) > len(expected):
        errors.append(f"{path}: duplicate managed source headers")
    return errors


def fix_content(path, data):
    expected = (expected_header(path),)
    bom, lines = split_content(data)
    newline = b"\r\n" if any(line.endswith(b"\r\n") for line in lines) else b"\n"
    # Only touch the initial header block, never examples or raw strings in the body.
    del lines[:managed_prefix(lines)]
    return bom + b"".join(header + newline for header in expected) + b"".join(lines)


def strip_content(path, data):
    errors = check_content(path, data)
    if errors:
        raise ValueError("\n".join(errors))
    bom, lines = split_content(data)

    del lines[0]
    return bom + b"".join(lines)


def tracked_files(root):
    result = subprocess.run(
        ["git", "ls-files", "--cached", "-z"], cwd=root,
        check=True, stdout=subprocess.PIPE,
    )
    return sorted(set(result.stdout.decode("utf-8").rstrip("\0").split("\0"))) if result.stdout else []


def validate(root, paths):
    errors = []
    for path in paths:
        if not is_source(path):
            continue
        try:
            errors.extend(check_content(path, regular_source(root, path).read_bytes()))
        except (ValueError, OSError) as error:
            errors.append(str(error))
    return errors


def prepare_pdf(root, paths, output):
    errors = validate(root, paths)
    if errors:
        raise ValueError("\n".join(errors))
    # Check all copied paths, including documents, before producing any output.
    for path in paths:
        regular_source(root, path)
    output = output.resolve()
    if output == root.resolve() or root.resolve() in output.parents:
        raise ValueError("PDF output directory must be outside the source tree")
    if output.exists() and (not output.is_dir() or any(output.iterdir())):
        raise ValueError("PDF output directory must be empty")
    output.mkdir(parents=True, exist_ok=True)
    for path in paths:
        source = root / path
        destination = output / path
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)
        if is_source(path):
            destination.write_bytes(strip_content(path, source.read_bytes()))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("check", "fix", "prepare-pdf"))
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if (args.command == "prepare-pdf") != (args.output is not None):
        parser.error("--output is required only for prepare-pdf")
    try:
        paths = tracked_files(ROOT)
        sources = [path for path in paths if is_source(path)]
        if args.command == "fix":
            updates = []
            for path in sources:
                file = regular_source(ROOT, path)
                original = file.read_bytes()
                updated = fix_content(path, original)
                if updated != original:
                    updates.append((file, updated))
            for file, updated in updates:
                file.write_bytes(updated)
            print(f"Updated {len(updates)} source headers.")
        if args.command == "prepare-pdf":
            prepare_pdf(ROOT, paths, args.output)
            print(f"Prepared PDF sources in {args.output}")
        else:
            errors = validate(ROOT, paths)
            if errors:
                raise ValueError("\n".join(errors))
            print(f"Source URLs verified: {len(sources)} C/C++ files.")
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        print(error, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
