#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$repo_root"

clang-format -i src/*.cpp include/*.hpp sample.cpp

echo "clang-tidy skipped (not enabled yet)."
