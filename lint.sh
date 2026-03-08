#!/usr/bin/env bash
set -euo pipefail

find src include examples tests -type f \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format -i {} +

echo "clang-tidy skipped (not enabled yet)."
