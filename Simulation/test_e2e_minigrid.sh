#!/usr/bin/env bash
set -euo pipefail

# Resolve runfiles paths for the binary and scenario
if [[ -n "${RUNFILES_DIR:-}" ]]; then
  BIN="$RUNFILES_DIR/_main/Simulation/evac"
  SCEN="$RUNFILES_DIR/_main/Simulation/slang/minigrid.slang"
else
  ROOT="${0}.runfiles/_main"
  BIN="$ROOT/Simulation/evac"
  SCEN="$ROOT/Simulation/slang/minigrid.slang"
fi

# Run in a writable temp area provided by Bazel test runner
WD="${TEST_TMPDIR:-$PWD}"
mkdir -p "$WD/outputs"
cd "$WD"

"$BIN" "$SCEN"

# Verify drawable output exists and is non-empty
test -s "outputs/minigridFinal.txt"

