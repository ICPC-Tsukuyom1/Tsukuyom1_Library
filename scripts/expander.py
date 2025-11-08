#!/usr/bin/env python3

import sys
import os
import re

def process_file(file_path, base_dir):
    abs_path = os.path.normpath(os.path.join(base_dir, file_path))
    output_lines = []

    with open(abs_path, 'r', encoding='utf-8') as f:
        for line in f:
            match = re.match(r'^\s*#include\s*"([^"]+)"', line)
            
            if match:
                output_lines.append(process_file(match.group(1), os.path.dirname(abs_path)))
            else:
                output_lines.append(line)
    output_lines.append(f"\n")

    return "".join(output_lines)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <root_cpp_file>", file=sys.stderr)
        sys.exit(1)

    root_file = sys.argv[1]
    
    print(process_file(root_file, os.path.dirname(os.path.abspath(root_file))))

if __name__ == "__main__":
    main()