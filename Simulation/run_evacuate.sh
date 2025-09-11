#!/usr/bin/env bash
set -euo pipefail

# Locate the evac binary in runfiles
if [[ -n "${RUNFILES_DIR:-}" ]]; then
  BIN="$RUNFILES_DIR/_main/Simulation/evac"
else
  BIN="${0}.runfiles/_main/Simulation/evac"
fi

# Resolve workspace directory and ensure outputs/ exists there
WORKSPACE_DIR="${BUILD_WORKSPACE_DIRECTORY:-$PWD}"
mkdir -p "$WORKSPACE_DIR/outputs"

# Resolve scenario path relative to the workspace if needed
ARGS=("$@")
if [[ ${#ARGS[@]} -ge 1 ]]; then
  SCEN="${ARGS[0]}"
  if [[ ! -f "$SCEN" && -f "$WORKSPACE_DIR/$SCEN" ]]; then
    ARGS[0]="$WORKSPACE_DIR/$SCEN"
  fi
fi

cd "$WORKSPACE_DIR"
exec "$BIN" "${ARGS[@]}"
