#!/bin/bash

set -euo pipefail

cd "$(dirname "$0")"
docs_dir="$PWD"
rm -f -- "$docs_dir/main.pdf"

temp_dir=$(mktemp -d "${TMPDIR:-/tmp}/tsukuyom1-pdf.XXXXXX")
cleanup() {
    status=$?
    if [ "$status" -ne 0 ]; then
        rm -f -- "$docs_dir/main.pdf"
    fi
    rm -rf -- "$temp_dir"
    exit "$status"
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

temp_root="$temp_dir/root"
mkdir -- "$temp_root"
PYTHONDONTWRITEBYTECODE=1 python3 "$docs_dir/../scripts/source_urls.py" prepare-pdf --output "$temp_root"
typst compile --root "$temp_root" "$temp_root/docs/main.typ" "$temp_dir/main.pdf"
mv -- "$temp_dir/main.pdf" "$docs_dir/main.pdf"
