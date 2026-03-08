#!/usr/bin/env bash
set -euo pipefail

clang-format -i src/*.cpp include/*.hpp sample.cpp

echo "clang-tidy skipped (not enabled yet)."
