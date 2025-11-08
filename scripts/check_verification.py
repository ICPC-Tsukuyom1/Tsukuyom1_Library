#!/usr/bin/env python3

import os
import glob
import re

INCLUDE_REGEX = re.compile(r'#include\s*"(.*?)"')

def find_all_source_files(root_dir: str) -> set[str]:
    all_files: set[str] = set()
    pattern = os.path.join(root_dir, '**', '*.cpp')
    for file in glob.glob(pattern, recursive=True):
        rel = os.path.relpath(file, root_dir)
        if rel.split(os.sep)[0] == 'verify':
            continue
        all_files.add(rel)
    return all_files

def find_verified_files(root_dir: str) -> set[str]:
    verified_files: set[str] = set()
    verify_pattern = os.path.join(root_dir, 'verify', '**', '*.cpp')
    test_files = glob.glob(verify_pattern, recursive=True)

    for test_file in test_files:
        with open(test_file, 'r', encoding='utf-8') as f:
            content = f.read()

        test_file_dir = os.path.dirname(test_file)
        for included_path in INCLUDE_REGEX.findall(content):
            abs_included_path = os.path.normpath(os.path.join(test_file_dir, included_path))
            relative_path = os.path.relpath(abs_included_path, root_dir)
            verified_files.add(relative_path)

    return verified_files

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    PROJECT_ROOT = os.path.abspath(os.path.join(script_dir, '..'))

    all_sources = find_all_source_files(PROJECT_ROOT)
    verified_sources = find_verified_files(PROJECT_ROOT)

    unverified_files = sorted(all_sources - verified_sources)

    if unverified_files:
        print("検証されていないファイル一覧:")
        for file_path in unverified_files:
            print(f"- {file_path}")
        print(f"合計: {len(unverified_files)} / {len(all_sources)} ファイル未検証")
    else:
        print("すべてのファイルが検証されています。")

