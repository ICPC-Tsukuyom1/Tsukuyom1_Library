#!/usr/bin/env python3

import glob
import gzip
import json
import os
import subprocess
import sys


def main() -> int:
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <problem> <source.cpp>", file=sys.stderr)
        return 2

    problem, source = sys.argv[1:]
    result = subprocess.run(
        ["gcov", "--json-format", f"a-{os.path.basename(source).removesuffix('.cpp')}.gcno"],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        print(result.stderr, file=sys.stderr)
        print("gcno files:", glob.glob("**/*.gcno", recursive=True), file=sys.stderr)
        return result.returncode

    json_files = glob.glob("*.gcov.json.gz")
    if not json_files:
        print("gcov did not produce a JSON coverage report", file=sys.stderr)
        print(result.stderr, file=sys.stderr)
        return 1

    project_root = os.path.realpath(".")
    function_counts: list[int] = []
    covered_lines = 0
    total_lines = 0
    for json_file in json_files:
        with gzip.open(json_file, "rt", encoding="utf-8") as report_file:
            report = json.load(report_file)
        for file_report in report.get("files", []):
            source_path = os.path.realpath(file_report["file"])
            if os.path.commonpath((project_root, source_path)) != project_root:
                continue
            function_counts.extend(
                int(function.get("execution_count", 0))
                for function in file_report.get("functions", [])
            )
            for line in file_report.get("lines", []):
                total_lines += 1
                covered_lines += int(line.get("count", 0) > 0)

    executed_functions = sum(count > 0 for count in function_counts)
    total_functions = len(function_counts)
    line_percent = 100 * covered_lines / total_lines if total_lines else 0
    function_percent = 100 * executed_functions / total_functions if total_functions else 0

    report = [
        f"## Coverage: {problem}",
        "",
        "| Metric | Covered | Total | Coverage |",
        "| --- | ---: | ---: | ---: |",
        f"| Functions | {executed_functions} | {total_functions} | {function_percent:.1f}% |",
        f"| Lines | {covered_lines} | {total_lines} | {line_percent:.1f}% |",
    ]

    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        with open(summary_path, "a", encoding="utf-8") as summary:
            summary.write("\n".join(report) + "\n")
    else:
        print("\n".join(report))

    if not total_functions and not total_lines:
        print("gcov produced no coverage records", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
