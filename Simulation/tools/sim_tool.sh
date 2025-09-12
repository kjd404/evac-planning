#!/usr/bin/env bash
set -euo pipefail

# Locate simulator binary in runfiles
if [[ -n "${RUNFILES_DIR:-}" ]]; then
  BIN="$RUNFILES_DIR/_main/Simulation/evac"
else
  BIN="${0}.runfiles/_main/Simulation/evac"
fi

exec "$BIN" "$@"

