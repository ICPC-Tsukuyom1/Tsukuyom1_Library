#!/usr/bin/env python3
"""Tests for the source URL checker and PDF copy."""

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import source_urls


class SourceUrlTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name) / "repo"
        self.root.mkdir()
        subprocess.run(["git", "init", "-q"], cwd=self.root, check=True)

    def write_tracked(self, files):
        for name, data in files.items():
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        subprocess.run(["git", "add", "-A"], cwd=self.root, check=True)

    def files(self):
        return source_urls.source_files(self.root)

    def test_check_finds_missing_and_wrong_urls(self):
        self.write_tracked({"a.cpp": b"int a;\n", "b.hpp": b"/* wrong URL */\n"})
        errors = source_urls.check(self.root, self.files())
        self.assertEqual(len(errors), 2)
        source_urls.fix(self.root, self.files())
        self.assertEqual(source_urls.check(self.root, self.files()), [])

    def test_check_rejects_duplicate_url_headers(self):
        header = source_urls.header(Path("a.cpp")).encode()
        self.write_tracked({"a.cpp": header + b"\n" + header + b"\nint a;\n"})
        self.assertEqual(len(source_urls.check(self.root, self.files())), 1)
        source_urls.fix(self.root, self.files())
        self.assertEqual(source_urls.check(self.root, self.files()), [])

    def test_fix_is_idempotent_and_preserves_source(self):
        body = b"/* Existing license notice. */\nint main() {}\n"
        self.write_tracked({"Graph/a.cpp": body})
        source_urls.fix(self.root, self.files())
        fixed = (self.root / "Graph/a.cpp").read_bytes()
        self.assertEqual(fixed, source_urls.header(Path("Graph/a.cpp")).encode() + b"\n" + body)
        source_urls.fix(self.root, self.files())
        self.assertEqual((self.root / "Graph/a.cpp").read_bytes(), fixed)

    def test_pdf_copy_strips_only_source_url_and_keeps_originals(self):
        code = b"//@yosupo a_plus_b\nint main() {}\n"
        license_file = b"CC0 license text\n"
        verify_code = b"//@yosupo a_plus_b\nint main() {}\n"
        self.write_tracked({"a.cpp": code, "verify/a.cpp": verify_code,
                            "LICENSE": license_file, "docs/page.typ": b"= Docs\n"})
        source_urls.fix(self.root, self.files())
        original_code = (self.root / "a.cpp").read_bytes()
        output = Path(self.temp.name) / "pdf-copy"
        source_urls.prepare_pdf(self.root, self.files(), output)
        self.assertEqual((output / "a.cpp").read_bytes(), code)
        self.assertEqual((output / "LICENSE").read_bytes(), license_file)
        self.assertEqual((output / "docs/page.typ").read_bytes(), b"= Docs\n")
        self.assertEqual((output / "verify/a.cpp").read_bytes(), verify_code)
        self.assertEqual((self.root / "a.cpp").read_bytes(), original_code)

    def test_pdf_copy_rejects_missing_header_without_output(self):
        self.write_tracked({"a.cpp": b"int a;\n"})
        output = Path(self.temp.name) / "pdf-copy"
        with self.assertRaises(ValueError):
            source_urls.prepare_pdf(self.root, self.files(), output)
        self.assertFalse(output.exists())

    def test_non_code_and_verify_files_are_not_required_to_have_headers(self):
        untouched = b"//@yosupo a_plus_b\nint main() {}\n"
        self.write_tracked({"README.md": b"# Docs\n", "settings.json": b"{}\n",
                            "verify/a.cpp": untouched, "a.cpp": b"int a;\n"})
        source_urls.fix(self.root, self.files())
        self.assertEqual((self.root / "README.md").read_bytes(), b"# Docs\n")
        self.assertEqual((self.root / "settings.json").read_bytes(), b"{}\n")
        self.assertEqual((self.root / "verify/a.cpp").read_bytes(), untouched)
        self.assertEqual([p.as_posix() for p in self.files()], ["a.cpp"])
        self.assertEqual(source_urls.check(self.root, self.files()), [])


if __name__ == "__main__":
    unittest.main()
