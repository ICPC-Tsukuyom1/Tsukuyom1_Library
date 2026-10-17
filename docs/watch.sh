#!/bin/bash

set -euo pipefail

cd "$(dirname "$0")"
docs_dir="$PWD"
repo_dir=$(dirname "$docs_dir")

temp_dir=$(mktemp -d "${TMPDIR:-/tmp}/tsukuyom1-pdf-watch.XXXXXX")
temp_root="$temp_dir/root"
stamp="$temp_dir/stamp"
sync_pid=""
typst_pid=""

cleanup() {
    status=$?
    for pid in "$sync_pid" "$typst_pid"; do
        if [ -n "$pid" ]; then
            kill "$pid" 2>/dev/null || true
        fi
    done
    rm -rf -- "$temp_dir"
    exit "$status"
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

# build.sh と同じく、URL行を除いたコピーを作る
prepare() {
    rm -rf -- "$temp_root"
    mkdir -p -- "$temp_root"
    PYTHONDONTWRITEBYTECODE=1 python3 "$docs_dir/../scripts/source_urls.py" prepare-pdf --output "$temp_root"
}

# typst watch は一時コピーを監視するため、元のソースが変更されたら作り直す
sync_loop() {
    while true; do
        sleep 1
        if [ -n "$(find "$repo_dir" -type f -newer "$stamp" \
                -not -path "$repo_dir/.git" -not -path "$repo_dir/.git/*" \
                -not -name '*.pdf' -print -quit 2>/dev/null)" ]; then
            prepare || echo "warning: failed to rebuild the URL-free copy" >&2
            touch "$stamp"
        fi
    done
}

prepare
touch "$stamp"
sync_loop &
sync_pid=$!
typst watch --root "$temp_root" "$temp_root/docs/main.typ" "$docs_dir/main.pdf" &
typst_pid=$!
wait "$typst_pid"
