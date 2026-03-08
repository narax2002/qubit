#!/usr/bin/env bash
set -euo pipefail

clang-format -i src/*.cpp include/*.hpp examples/*.cpp tests/*.cpp

echo "clang-tidy skipped (not enabled yet)."
