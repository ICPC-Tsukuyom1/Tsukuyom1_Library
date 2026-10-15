#!/usr/bin/env python3
"""Check C/C++ source URLs and make a URL-free copy for the print PDF."""

import argparse
import shutil
import subprocess
import sys
from pathlib import Path
from urllib.parse import quote

ROOT = Path(__file__).resolve().parent.parent
BASE_URL = "https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/"
EXTENSIONS = {".cpp", ".cc", ".cxx", ".c", ".h", ".hh", ".hpp", ".hxx", ".ipp", ".tpp"}


def source_files(root):
    result = subprocess.run(
        ["git", "ls-files", "-z"], cwd=root, check=True, capture_output=True
    )
    return [Path(p) for p in result.stdout.decode().split("\0") if p
            and Path(p).suffix in EXTENSIONS]


def header(path):
    url = BASE_URL + quote(path.as_posix(), safe="/")
    return f"/* {url} */"


def check(root, files):
    errors = []
    for path in files:
        file = root / path
        if file.is_symlink() or not file.is_file():
            errors.append(f"{path}: not a regular file")
            continue
        lines = file.read_bytes().splitlines()
        actual = lines[0].decode("utf-8", errors="replace") if lines else ""
        if actual != header(path):
            errors.append(f"{path}: first line must be {header(path)}")
        elif len(lines) > 1 and lines[1].startswith(b"/* https://github.com/ICPC-Tsukuyom1/"):
            errors.append(f"{path}: duplicate source URL headers")
    return errors


def fix(root, files):
    for path in files:
        file = root / path
        if file.is_symlink() or not file.is_file():
            raise ValueError(f"{path}: not a regular file")
        data = file.read_bytes()
        lines = data.splitlines(keepends=True)
        newline = b"\r\n" if lines and lines[0].endswith(b"\r\n") else b"\n"
        while lines and lines[0].startswith(b"/* https://github.com/ICPC-Tsukuyom1/"):
            del lines[0]
        file.write_bytes(header(path).encode() + newline + b"".join(lines))


def prepare_pdf(root, files, output):
    errors = check(root, files)
    if errors:
        raise ValueError("\n".join(errors))
    output = output.resolve()
    root = root.resolve()
    if output == root or root in output.parents:
        raise ValueError("PDF output must be outside the repository")
    if output.exists() and (not output.is_dir() or any(output.iterdir())):
        raise ValueError("PDF output directory must be empty")
    tracked = [name for name in subprocess.run(
        ["git", "ls-files", "-z"], cwd=root, check=True, capture_output=True
    ).stdout.decode().split("\0") if name]
    for name in tracked:
        source = root / name
        if source.is_symlink() or not source.is_file():
            raise ValueError(f"{name}: not a regular file")
    output.mkdir(parents=True, exist_ok=True)
    for name in tracked:
        source = root / name
        destination = output / name
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)
        if Path(name).suffix in EXTENSIONS:
            lines = destination.read_bytes().splitlines(keepends=True)
            destination.write_bytes(b"".join(lines[1:]))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("check", "fix", "prepare-pdf"))
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if (args.command == "prepare-pdf") != (args.output is not None):
        parser.error("--output is required only for prepare-pdf")
    try:
        files = source_files(ROOT)
        if args.command == "fix":
            fix(ROOT, files)
        if args.command == "prepare-pdf":
            prepare_pdf(ROOT, files, args.output)
        else:
            errors = check(ROOT, files)
            if errors:
                raise ValueError("\n".join(errors))
            print(f"Source URLs verified: {len(files)} C/C++ files.")
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(error, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
