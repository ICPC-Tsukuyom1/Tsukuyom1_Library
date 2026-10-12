#!/usr/bin/env python3

import gzip
import json
import os
import pathlib
import sys


def relative_source(source: str, root: pathlib.Path) -> str | None:
    path = pathlib.Path(source)
    if not path.is_absolute():
        path = root / path
    try:
        return path.resolve().relative_to(root).as_posix()
    except ValueError:
        return None


def line_ranges(line_numbers: list[int]) -> str:
    if not line_numbers:
        return ""
    ranges = []
    start = previous = line_numbers[0]
    for line_number in line_numbers[1:]:
        if line_number != previous + 1:
            ranges.append(str(start) if start == previous else f"{start}–{previous}")
            start = line_number
        previous = line_number
    ranges.append(str(start) if start == previous else f"{start}–{previous}")
    return ", ".join(ranges)


def main() -> int:
    data_dir = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "coverage-data")
    root = pathlib.Path.cwd().resolve()
    library_files = sorted(
        path.relative_to(root).as_posix()
        for path in root.rglob("*.cpp")
        if path.relative_to(root).parts[0] != "verify"
    )

    functions: dict[str, dict[tuple[int, str], bool]] = {
        path: {} for path in library_files
    }
    lines: dict[str, dict[int, bool]] = {path: {} for path in library_files}
    verifiers: dict[str, set[str]] = {path: set() for path in library_files}
    reports = sorted(data_dir.glob("*.gcov.json.gz")) if data_dir.exists() else []

    for report_path in reports:
        with gzip.open(report_path, "rt", encoding="utf-8") as report_file:
            report = json.load(report_file)
        file_reports = report.get("files", [])
        verify_sources = sorted(
            source
            for file_report in file_reports
            if (source := relative_source(file_report["file"], root))
            and source.startswith("verify/")
            and source.endswith(".cpp")
        )

        for file_report in file_reports:
            relative_path = relative_source(file_report["file"], root)
            if relative_path not in functions:
                continue

            verifiers[relative_path].update(verify_sources)
            for function in file_report.get("functions", []):
                key = (
                    int(function.get("start_line", 0)),
                    function.get("demangled_name") or function.get("name", ""),
                )
                functions[relative_path][key] = (
                    functions[relative_path].get(key, False)
                    or int(function.get("execution_count", 0)) > 0
                )
            for line in file_report.get("lines", []):
                line_number = int(line.get("line_number", 0))
                lines[relative_path][line_number] = (
                    lines[relative_path].get(line_number, False)
                    or int(line.get("count", 0)) > 0
                )

    rows = []
    total_functions = covered_functions = total_lines = covered_lines = 0
    for path in library_files:
        file_functions = functions[path]
        file_lines = lines[path]
        total_functions += len(file_functions)
        covered_functions += sum(file_functions.values())
        total_lines += len(file_lines)
        covered_lines += sum(file_lines.values())

        if not file_functions and not file_lines:
            rows.append(f"| `{path}` | — | — | — | — |")
            continue

        function_count = sum(file_functions.values())
        line_count = sum(file_lines.values())
        function_rate = 100 * function_count / len(file_functions) if file_functions else 100
        line_rate = 100 * line_count / len(file_lines) if file_lines else 100
        incomplete = function_count < len(file_functions) or line_count < len(file_lines)
        warning = "⚠️ " if incomplete else ""

        missed_functions = sorted(
            name for (_, name), covered in file_functions.items() if not covered
        )
        missed_lines = sorted(line_number for line_number, covered in file_lines.items() if not covered)
        missing = []
        if missed_functions:
            escaped_names = (name.replace("|", "\\|") for name in missed_functions)
            missing.append("functions: " + ", ".join(f"`{name}`" for name in escaped_names))
        if missed_lines:
            missing.append("lines: " + line_ranges(missed_lines))
        missing_summary = warning + ("; ".join(missing) if missing else "—")
        verify_summary = "<br>".join(f"`{source}`" for source in sorted(verifiers[path])) or "—"
        function_summary = (
            f"{function_count}/{len(file_functions)} ({function_rate:.1f}%)"
            if file_functions
            else "—"
        )
        line_summary = (
            f"{line_count}/{len(file_lines)} ({line_rate:.1f}%)"
            if file_lines
            else "—"
        )
        rows.append(
            f"| `{path}` | {function_summary} | {line_summary} | {missing_summary} | {verify_summary} |"
        )

    function_rate = 100 * covered_functions / total_functions if total_functions else 0
    line_rate = 100 * covered_lines / total_lines if total_lines else 0
    report_lines = [
        "# Library C++ Coverage",
        "",
        f"Collected {len(reports)} verify coverage report(s). Files absent from all reports are shown as `—`.",
        "Verify files are listed when their translation unit includes the library file.",
        "",
        "| Library `.cpp` file | Functions | Lines | Uncovered functions / lines | Reached from verify files |",
        "| --- | ---: | ---: | --- | --- |",
        *rows,
        (
            f"| **Total** | **{covered_functions}/{total_functions} ({function_rate:.1f}%)** "
            f"| **{covered_lines}/{total_lines} ({line_rate:.1f}%)** | | |"
        ),
    ]
    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        with open(summary_path, "a", encoding="utf-8") as summary:
            summary.write("\n".join(report_lines) + "\n")
    else:
        print("\n".join(report_lines))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
