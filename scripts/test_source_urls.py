"""Regression tests for one-line C/C++ citations and PDF preparation."""

import codecs
import shutil
import stat
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

# Support direct execution and unittest discovery from the repository root.
sys.path.insert(0, str(Path(__file__).resolve().parent))
import source_urls


BASE_URL = "https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/"
SCRIPTS = Path(__file__).resolve().parent
ORIGINAL_LICENSE_BODY = (
    b"// Copyright (c) 1999 Original Author\n"
    b"// SPDX-License-Identifier: BSD-3-Clause\n"
    b"// License: preserve this original notice verbatim\n"
    b"/* Original license terms.\nAll rights reserved. */\n"
)
NONCODE = {
    "docs/arbitrary.typ": b"= Title\n```cpp\n// Source: example\n```\n",
    "data/settings.json": b'{"setting": true}\n',
    "scripts/tool.py": b"#!/usr/bin/env python3\n# coding: latin-1\nprint(1)\n",
    "run.sh": b"#!/bin/sh\necho ok\n",
    "LICENSE": b"CC0 1.0 Universal\n\nPublic domain dedication\n",
    "assets/image.bin": b"\x00\xff\x80\r\n",
    "README.md": b"# Examples\n```cpp\n// SPDX-License-Identifier: MIT\n```\n",
    ".clang-format": b"BasedOnStyle: Google\n",
    "unknown": b"arbitrary bytes\xff",
    "legacy.typ": (b"/* Source: " + BASE_URL.encode() + b"legacy.typ */\r\n= Title\r\n"),
}


def header_block(path, newline=b"\n"):
    return source_urls.expected_header(path) + newline


class ContentTests(unittest.TestCase):
    def test_source_extensions_and_exact_header_block(self):
        extensions = {".cpp", ".cc", ".cxx", ".c", ".h", ".hh", ".hpp", ".hxx", ".ipp", ".tpp"}
        self.assertEqual(source_urls.SOURCE_EXTENSIONS, extensions)
        for extension in sorted(extensions):
            path = "code/a" + extension
            with self.subTest(path=path):
                self.assertTrue(source_urls.is_source(path))
                self.assertEqual(source_urls.expected_header(path),
                                 f"/* {BASE_URL}{path} */".encode())
                body = b"int x;\n"
                fixed = source_urls.fix_content(path, body)
                self.assertEqual(fixed, header_block(path) + body)
                self.assertEqual(source_urls.check_content(path, fixed), [])
                self.assertEqual(source_urls.fix_content(path, fixed), fixed)
                self.assertEqual(source_urls.strip_content(path, fixed), body)

    def test_noncode_is_not_a_supported_content_format(self):
        for path in (*NONCODE, "a.CPP", "a.cpp.bak"):
            with self.subTest(path=path):
                self.assertFalse(source_urls.is_source(path))
                with self.assertRaisesRegex(ValueError, "not a supported C/C\\+\\+ source file"):
                    source_urls.expected_header(path)
                for function in (source_urls.check_content, source_urls.fix_content, source_urls.strip_content):
                    with self.assertRaises(ValueError):
                        function(path, b"body\n")

    def test_url_encoding_and_case(self):
        path = "Math/日本語 space #%.cpp"
        expected = BASE_URL + "Math/%E6%97%A5%E6%9C%AC%E8%AA%9E%20space%20%23%25.cpp"
        self.assertEqual(source_urls.source_url(path), expected)
        fixed = source_urls.fix_content(path, b"int x;\n")
        self.assertEqual(fixed, header_block(path) + b"int x;\n")
        self.assertEqual(source_urls.check_content(path, fixed), [])
        self.assertTrue(source_urls.check_content(path.lower(), fixed))

    def test_bom_crlf_empty_and_unterminated_body(self):
        for bom in (b"", codecs.BOM_UTF8):
            for body, newline in ((b"", b"\n"), (b"int x;", b"\n"),
                                  (b"int x;\n", b"\n"), (b"int x;\r\n", b"\r\n")):
                with self.subTest(bom=bom, body=body):
                    fixed = source_urls.fix_content("a.cpp", bom + body)
                    self.assertEqual(fixed, bom + header_block("a.cpp", newline) + body)
                    self.assertEqual(source_urls.check_content("a.cpp", fixed), [])
                    self.assertEqual(source_urls.fix_content("a.cpp", fixed), fixed)
                    self.assertEqual(source_urls.strip_content("a.cpp", fixed),
                                     bom + body)

    def test_check_rejects_missing_wrong_and_misplaced_headers(self):
        path = "new.cpp"
        valid = header_block(path)
        cases = {
            "missing": b"int x;\n",
            "wrong repository": valid.replace(b"ICPC-Tsukuyom1/", b"another-owner/", 1),
            "wrong branch": valid.replace(b"/main/", b"/other/"),
            "renamed": valid.replace(b"new.cpp", b"old.cpp"),
            "wrong style": valid.replace(b"/* ", b"// "),
            "misplaced": b"int x;\n" + valid,
            "empty": b"",
            "blank first line": b"\n" + valid,
            "duplicate source": valid + valid,
            "adjacent stale source": valid + header_block("old.cpp"),
        }
        for case, data in cases.items():
            with self.subTest(case=case):
                errors = source_urls.check_content(path, data)
                self.assertTrue(errors)
                self.assertTrue(all(path in error for error in errors))
                if case in ("duplicate source", "adjacent stale source"):
                    self.assertIn("duplicate", "\n".join(errors))
                with self.assertRaises(ValueError):
                    source_urls.strip_content(path, data)
                fixed = source_urls.fix_content(path, data)
                self.assertEqual(source_urls.check_content(path, fixed), [])
                self.assertEqual(source_urls.fix_content(path, fixed), fixed)

    def test_check_and_strip_preserve_source_examples_after_the_initial_prefix(self):
        path = "a.cpp"
        for body in (b"", b"\n" + header_block(path), b"\n" + header_block("old.cpp"),
                     ORIGINAL_LICENSE_BODY, b"int x;\n" + header_block("old.cpp")):
            with self.subTest(body=body):
                data = header_block(path) + body
                self.assertEqual(source_urls.check_content(path, data), [])
                self.assertEqual(source_urls.strip_content(path, data), body)

    def test_fix_normalizes_only_consecutive_initial_source_lines(self):
        path = "a.cpp"
        body = (ORIGINAL_LICENSE_BODY + b"//@yosupo a_plus_b\n"
                b"/* Source: https://example.com/original */\n"
                b"// https://github.com/other/library/blob/main/a.cpp\nint x;\n")
        stale = header_block("old.cpp")
        for prefix in (b"", stale, stale + stale, header_block(path) + stale):
            with self.subTest(prefix=prefix):
                fixed = source_urls.fix_content(path, prefix + body + stale)
                self.assertEqual(fixed, header_block(path) + body + stale)
                self.assertEqual(source_urls.check_content(path, fixed), [])
                self.assertEqual(source_urls.fix_content(path, fixed), fixed)
                self.assertEqual(source_urls.strip_content(path, fixed), body + stale)
        self.assertEqual(source_urls.fix_content(path, source_urls.expected_header("old.cpp")),
                         header_block(path))

    def test_fix_and_strip_preserve_all_original_license_comments(self):
        path = "a.cpp"
        legacy_notices = (b"// SPDX-License-Identifier: MIT\n"
                          b"// Copyright (c) 2026 ICPC-Tsukuyom1 contributors\n")
        stale = header_block("old.cpp")
        for body in (ORIGINAL_LICENSE_BODY, legacy_notices,
                     ORIGINAL_LICENSE_BODY + stale + legacy_notices):
            for bom in (b"", codecs.BOM_UTF8):
                for newline in (b"\n", b"\r\n"):
                    original_body = body.replace(b"\n", newline) + b"int x;"
                    for prefix in (b"", header_block(path, newline),
                                   header_block("old.cpp", newline) * 2):
                        with self.subTest(body=body, bom=bom, newline=newline, prefix=prefix):
                            fixed = source_urls.fix_content(path, bom + prefix + original_body)
                            self.assertEqual(fixed, bom + header_block(path, newline) + original_body)
                            self.assertEqual(source_urls.check_content(path, fixed), [])
                            self.assertEqual(source_urls.fix_content(path, fixed), fixed)
                            self.assertEqual(source_urls.strip_content(path, fixed), bom + original_body)

    def test_raw_strings_and_code_examples_remain_byte_identical(self):
        path = "raw.cpp"
        example = header_block(path) + header_block("old.cpp")
        bodies = (
            b'const char* example = R"example(\n' + example + b')example";\n',
            b"/* Code example:\n```cpp\n" + example + b"```\n*/\nint x;\n",
        )
        for body in bodies:
            for prefix in (b"", header_block("old.cpp"), header_block(path)):
                with self.subTest(body=body, prefix=prefix):
                    fixed = source_urls.fix_content(path, prefix + body)
                    self.assertEqual(fixed, header_block(path) + body)
                    self.assertEqual(source_urls.check_content(path, fixed), [])
                    self.assertEqual(source_urls.fix_content(path, fixed), fixed)
                    self.assertEqual(source_urls.strip_content(path, fixed), body)

    @unittest.skipUnless(shutil.which("clang-format"), "clang-format is not installed")
    def test_clang_format_preserves_source_and_original_license_comments(self):
        data = header_block("a.cpp") + ORIGINAL_LICENSE_BODY + b"int main(){return 0;}\n"
        result = subprocess.run(
            ["clang-format", f"--style=file:{SCRIPTS.parent / '.clang-format'}"],
            input=data, capture_output=True, check=True, timeout=20,
        )
        self.assertTrue(result.stdout.startswith(header_block("a.cpp") + ORIGINAL_LICENSE_BODY))
        self.assertEqual(source_urls.check_content("a.cpp", result.stdout), [])


class RepositoryTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        self.root = self.directory / "source"
        self.root.mkdir()
        self.output = self.directory / "pdf"
        self.git("init", "--quiet")

    def git(self, *args):
        return subprocess.run(["git", "--no-pager", *args], cwd=self.root,
                              capture_output=True, check=True, timeout=20).stdout

    def write(self, path, data, mode=0o644):
        file = self.root / path
        file.parent.mkdir(parents=True, exist_ok=True)
        file.write_bytes(data)
        file.chmod(mode)
        return file

    def cli(self, *args):
        # Use the real CLI policy, changing only its repository location.
        bootstrap = ("import pathlib, sys; "
                     "sys.path.insert(0, sys.argv.pop(1)); import source_urls; "
                     "source_urls.ROOT = pathlib.Path(sys.argv.pop(1)); "
                     "sys.exit(source_urls.main())")
        return subprocess.run([sys.executable, "-B", "-c", bootstrap, str(SCRIPTS), str(self.root), *args],
                              capture_output=True, text=True, timeout=20)

    def test_validate_and_cli_fix_skip_all_noncode_unchanged(self):
        for path, data in NONCODE.items():
            self.write(path, data, 0o755 if path.endswith((".py", ".sh")) else 0o640)
        self.git("add", "--all")
        paths = source_urls.tracked_files(self.root)
        originals = {path: ((self.root / path).read_bytes(),
                            stat.S_IMODE((self.root / path).stat().st_mode)) for path in paths}
        index = (self.root / ".git/index").read_bytes()
        self.assertEqual(source_urls.validate(self.root, paths), [])
        for command in ("check", "fix", "fix"):
            result = self.cli(command)
            self.assertEqual(result.returncode, 0, result.stderr)
            if command == "fix":
                self.assertIn("Updated 0", result.stdout)
            for path, (data, mode) in originals.items():
                with self.subTest(command=command, path=path):
                    self.assertEqual((self.root / path).read_bytes(), data)
                    self.assertEqual(stat.S_IMODE((self.root / path).stat().st_mode), mode)
            self.assertEqual((self.root / ".git/index").read_bytes(), index)

    def test_prepare_pdf_copies_all_files_preserving_notices_modes_and_index(self):
        bodies = dict(NONCODE)
        bodies["code/a.cpp"] = (ORIGINAL_LICENSE_BODY + b"//@yosupo a_plus_b\n// License: MIT\n"
                                b"/* Source: https://example.com/a */\nint x;\n")
        bodies["code/b.hpp"] = codecs.BOM_UTF8 + b"int y;\r\n"
        for path, body in bodies.items():
            data = source_urls.fix_content(path, body) if source_urls.is_source(path) else body
            self.write(path, data, 0o755 if path == "run.sh" else 0o640)
        self.git("add", "--all")
        self.write("untracked.cpp", b"not copied\n")
        paths = source_urls.tracked_files(self.root)
        self.assertEqual(paths, sorted(bodies))
        originals = {path: ((self.root / path).read_bytes(),
                            stat.S_IMODE((self.root / path).stat().st_mode)) for path in paths}
        index = (self.root / ".git/index").read_bytes()
        staged = self.git("ls-files", "--stage")
        source_urls.prepare_pdf(self.root, paths, self.output)
        copied = sorted(str(file.relative_to(self.output)) for file in self.output.rglob("*") if file.is_file())
        self.assertEqual(copied, paths)
        for path in paths:
            with self.subTest(path=path):
                original, mode = originals[path]
                self.assertEqual((self.root / path).read_bytes(), original)
                self.assertEqual(stat.S_IMODE((self.root / path).stat().st_mode), mode)
                expected = original
                if source_urls.is_source(path):
                    bom, lines = source_urls.split_content(original)
                    expected = bom + b"".join(lines[1:])

                    self.assertNotIn(source_urls.expected_header(path), expected)
                self.assertEqual((self.output / path).read_bytes(), expected)
                self.assertEqual((self.output / path).read_bytes(), bodies[path])
                self.assertEqual(stat.S_IMODE((self.output / path).stat().st_mode), mode)
        self.assertEqual((self.root / ".git/index").read_bytes(), index)
        self.assertEqual(self.git("ls-files", "--stage"), staged)
        self.assertFalse((self.output / ".git").exists())
        self.assertFalse((self.output / "untracked.cpp").exists())

    def test_prepare_pdf_rejects_source_and_populated_outputs(self):
        self.write("a.cpp", header_block("a.cpp") + b"int x;\n")
        self.output.mkdir()
        sentinel = self.output / "keep.txt"
        sentinel.write_bytes(b"keep")
        output_file = self.directory / "file"
        output_file.write_bytes(b"keep")
        for output in (self.root, self.root / "nested", self.output, output_file):
            with self.subTest(output=output):
                with self.assertRaises(ValueError):
                    source_urls.prepare_pdf(self.root, ["a.cpp"], output)
        self.assertEqual(sentinel.read_bytes(), b"keep")
        self.assertEqual(output_file.read_bytes(), b"keep")
        self.assertFalse((self.root / "nested").exists())

    def test_invalid_input_creates_no_pdf_copy(self):
        self.write("a.cpp", header_block("a.cpp") + b"int x;\n")
        self.write("z.cpp", b"missing header\n")
        self.git("add", "--all")
        for existing_output in (False, True):
            with self.subTest(existing_output=existing_output):
                if existing_output:
                    self.output.mkdir()
                with self.assertRaises(ValueError):
                    source_urls.prepare_pdf(self.root, ["a.cpp", "z.cpp"], self.output)
                result = self.cli("prepare-pdf", "--output", str(self.output))
                self.assertEqual(result.returncode, 1, result.stderr)
                self.assertIn("z.cpp", result.stderr)
                if existing_output:
                    self.assertEqual(list(self.output.iterdir()), [])
                else:
                    self.assertFalse(self.output.exists())

    def test_validate_rejects_missing_symlink_and_directory_sources(self):
        target = self.write("a.cpp", header_block("a.cpp"))
        (self.root / "link.cpp").symlink_to(target)
        (self.root / "directory.cpp").mkdir()
        errors = source_urls.validate(self.root, ["missing.cpp", "link.cpp", "directory.cpp"])
        self.assertEqual(len(errors), 3)
        self.assertIn("missing.cpp: expected a regular file", errors[0])
        self.assertIn("link.cpp: symlinks", errors[1])
        self.assertIn("directory.cpp: expected a regular file", errors[2])

    def test_symlink_parent_rejects_fix_and_prepare_without_partial_writes(self):
        path = "linked/nested/a.cpp"
        original = b"int external = 1;\n"
        self.write(path, original, 0o640)
        first = self.write("a.cpp", b"int untouched;\n")
        self.git("add", "--all")
        index = (self.root / ".git/index").read_bytes()
        external = self.directory / "external"
        (self.root / "linked").rename(external)
        (self.root / "linked").symlink_to(external, target_is_directory=True)
        external_file = external / "nested/a.cpp"
        errors = source_urls.validate(self.root, [path])
        self.assertEqual(len(errors), 1)
        self.assertIn(path + ": symlinks", errors[0])
        for args in (("fix",), ("prepare-pdf", "--output", str(self.output))):
            result = self.cli(*args)
            self.assertEqual(result.returncode, 1, result.stderr)
            self.assertIn("symlinks", result.stderr)
        with self.assertRaisesRegex(ValueError, "symlinks"):
            source_urls.prepare_pdf(self.root, [path], self.output)
        self.assertFalse(self.output.exists())
        self.assertEqual(first.read_bytes(), b"int untouched;\n")
        self.assertEqual(external_file.read_bytes(), original)
        self.assertEqual(stat.S_IMODE(external_file.stat().st_mode), 0o640)
        self.assertEqual((self.root / ".git/index").read_bytes(), index)

    def test_prepare_preflights_noncode_paths_before_creating_output(self):
        self.write("a.cpp", header_block("a.cpp"))
        external = self.directory / "external"
        external.mkdir()
        (external / "notes.typ").write_bytes(b"= External\n")
        (self.root / "linked").symlink_to(external, target_is_directory=True)
        (self.root / "link.json").symlink_to(external / "notes.typ")
        for path in ("linked/notes.typ", "link.json", "missing.typ"):
            with self.subTest(path=path):
                self.assertEqual(source_urls.validate(self.root, ["a.cpp", path]), [])
                with self.assertRaises(ValueError):
                    source_urls.prepare_pdf(self.root, ["a.cpp", path], self.output)
                self.assertFalse(self.output.exists())
        self.assertEqual((external / "notes.typ").read_bytes(), b"= External\n")

    def test_resolved_escape_is_rejected(self):
        external_file = self.directory / "outside.cpp"
        original = header_block("../outside.cpp") + b"int external = 1;\n"
        external_file.write_bytes(original)
        paths = ["../outside.cpp"]
        errors = source_urls.validate(self.root, paths)
        self.assertEqual(len(errors), 1)
        self.assertIn("inside the repository", errors[0])
        with self.assertRaisesRegex(ValueError, "inside the repository"):
            source_urls.prepare_pdf(self.root, paths, self.output)
        self.assertFalse(self.output.exists())
        self.assertEqual(external_file.read_bytes(), original)

    def test_cli_check_fix_idempotence_and_prepare_pdf(self):
        body = b"int x;\n"
        file = self.write("a.cpp", body, 0o755)
        self.write("LICENSE", NONCODE["LICENSE"])
        self.git("add", "--all")
        index = (self.root / ".git/index").read_bytes()
        result = self.cli("check")
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertIn("a.cpp", result.stderr)
        self.assertEqual(file.read_bytes(), body)
        result = self.cli("fix")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Updated 1", result.stdout)
        fixed = header_block("a.cpp") + body
        self.assertEqual(file.read_bytes(), fixed)
        result = self.cli("fix")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Updated 0", result.stdout)
        self.assertEqual(file.read_bytes(), fixed)
        self.assertEqual(stat.S_IMODE(file.stat().st_mode), 0o755)
        self.assertEqual((self.root / ".git/index").read_bytes(), index)
        result = self.cli("check")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("1 C/C++ files", result.stdout)
        result = self.cli("prepare-pdf", "--output", str(self.output))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.output / "a.cpp").read_bytes(), body)
        self.assertEqual((self.output / "LICENSE").read_bytes(), NONCODE["LICENSE"])
        self.assertEqual(file.read_bytes(), fixed)
        self.assertEqual((self.root / ".git/index").read_bytes(), index)

    def test_cli_accepts_sources_without_notices_and_preserves_original_licenses(self):
        path = "a.cpp"
        file = self.write(path, header_block(path))
        self.write("LICENSE", NONCODE["LICENSE"])
        self.git("add", "--all")
        index = (self.root / ".git/index").read_bytes()
        for number, body in enumerate((b"int x;\n", ORIGINAL_LICENSE_BODY + b"int x;\n")):
            with self.subTest(body=body):
                original = header_block(path) + body
                file.write_bytes(original)
                for command in ("check", "fix"):
                    result = self.cli(command)
                    self.assertEqual(result.returncode, 0, result.stderr)
                    self.assertEqual(file.read_bytes(), original)
                output = self.directory / f"pdf-{number}"
                result = self.cli("prepare-pdf", "--output", str(output))
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual((output / path).read_bytes(), body)
                self.assertEqual((output / "LICENSE").read_bytes(), NONCODE["LICENSE"])
                self.assertEqual((self.root / "LICENSE").read_bytes(), NONCODE["LICENSE"])
                self.assertEqual(file.read_bytes(), original)
                self.assertEqual((self.root / ".git/index").read_bytes(), index)

    def test_cli_output_argument_rules(self):
        for args in (("prepare-pdf",), ("check", "--output", str(self.output)),
                     ("fix", "--output", str(self.output))):
            with self.subTest(args=args):
                result = self.cli(*args)
                self.assertEqual(result.returncode, 2, result.stderr)
                self.assertIn("--output", result.stderr)

    def test_expander_preserves_root_and_dependency_sources_and_original_licenses(self):
        dependency = header_block("lib/dependency.cpp") + ORIGINAL_LICENSE_BODY + b"int dependency = 1;\n"
        root = header_block("root.cpp") + ORIGINAL_LICENSE_BODY + b'#include "lib/dependency.cpp"\nint main() {}\n'
        self.write("lib/dependency.cpp", dependency)
        root_file = self.write("root.cpp", root)
        result = subprocess.run([sys.executable, "-B", str(SCRIPTS / "expander.py"), str(root_file.resolve())],
                                capture_output=True, check=True, timeout=20)
        for path in ("root.cpp", "lib/dependency.cpp"):
            self.assertEqual(result.stdout.count(source_urls.expected_header(path)), 1)
            self.assertIn(header_block(path), result.stdout)
        self.assertEqual(result.stdout.count(ORIGINAL_LICENSE_BODY), 2)
        self.assertIn(b"int dependency = 1;", result.stdout)
        self.assertIn(b"int main() {}", result.stdout)
        self.assertNotIn(b'#include "lib/dependency.cpp"', result.stdout)


if __name__ == "__main__":
    unittest.main()
