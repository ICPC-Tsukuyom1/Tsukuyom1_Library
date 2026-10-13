#!/usr/bin/env python3

import glob
import hashlib
import os
import shutil
import subprocess
import sys


def main() -> int:
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <problem> <source.cpp>", file=sys.stderr)
        return 2

    problem, source = sys.argv[1:]
    gcno_file = f"a-{os.path.basename(source).removesuffix('.cpp')}.gcno"
    result = subprocess.run(
        ["gcov", "--json-format", gcno_file],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        print(result.stderr, file=sys.stderr)
        return result.returncode

    json_files = glob.glob("*.gcov.json.gz")
    if not json_files:
        print("gcov did not produce a JSON coverage report", file=sys.stderr)
        print(result.stderr, file=sys.stderr)
        return 1

    output_dir = "coverage-data"
    os.makedirs(output_dir, exist_ok=True)
    source_hash = hashlib.sha256(source.encode("utf-8")).hexdigest()[:16]
    job_name = os.environ.get("GITHUB_JOB", "verify")
    artifact_name = f"coverage-{job_name}-{source_hash}"
    destination = os.path.join(output_dir, f"{job_name}-{source_hash}.gcov.json.gz")
    shutil.move(json_files[0], destination)
    output_path = os.environ.get("GITHUB_OUTPUT")
    if output_path:
        with open(output_path, "a", encoding="utf-8") as output:
            output.write(f"artifact_name={artifact_name}\n")
    print(f"Coverage data for {problem} saved to {destination}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
