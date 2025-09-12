#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "usage: evac_viz_run <scenario.slang> [--gif docs/demo.gif] [--fps 30] [--duration 10] [--edgewidth prob|const]" >&2
  exit 2
fi

SCEN_ARG="$1"; shift || true

# Resolve runfiles
if [[ -n "${RUNFILES_DIR:-}" ]]; then
  BIN="$RUNFILES_DIR/_main/Simulation/evac"
  VIZ="$RUNFILES_DIR/_main/Simulation/tools/viz_gif.py"
else
  ROOT="${0}.runfiles/_main"
  BIN="$ROOT/Simulation/evac"
  VIZ="$ROOT/Simulation/tools/viz_gif.py"
fi

# Resolve workspace
WORKSPACE_DIR="${BUILD_WORKSPACE_DIRECTORY:-$PWD}"

# Ensure outputs/ exists and run sim
mkdir -p "$WORKSPACE_DIR/outputs" "$WORKSPACE_DIR/docs"

# Map scenario path to workspace
SCEN="$SCEN_ARG"
if [[ ! -f "$SCEN" && -f "$WORKSPACE_DIR/$SCEN_ARG" ]]; then
  SCEN="$WORKSPACE_DIR/$SCEN_ARG"
fi

"$BIN" "$SCEN"

# Extract city name from the scenario
CITY=$(grep -E '^\s*city\s+' "$SCEN" | head -n1 | awk '{print $2}')
if [[ -z "$CITY" ]]; then
  echo "Could not determine city name from scenario; expected 'city <name> N DEGREE'" >&2
  exit 1
fi

INFILE="$WORKSPACE_DIR/outputs/${CITY}Final.txt"
GIFFILE="$WORKSPACE_DIR/docs/${CITY}_anim.gif"

# pass-through args for viz
FPS=30; DURATION=10; EDGEWIDTH=prob
OUT_OVERRIDE=""
TRAILS_FLAG="--trails"
while [[ $# -gt 0 ]]; do
  case "$1" in
    --gif) OUT_OVERRIDE="$2"; shift 2;;
    --fps) FPS="$2"; shift 2;;
    --duration) DURATION="$2"; shift 2;;
    --edgewidth) EDGEWIDTH="$2"; shift 2;;
    --no-trails) TRAILS_FLAG=""; shift;;
    *) shift;;
  esac
done

[[ -n "$OUT_OVERRIDE" ]] && GIFFILE="$OUT_OVERRIDE"

python3 "$VIZ" \
  --input "$INFILE" \
  --outfile "$GIFFILE" \
  --width 700 \
  --fps "$FPS" \
  --duration "$DURATION" \
  --edgewidth "$EDGEWIDTH" \
  ${TRAILS_FLAG}

echo "Wrote $GIFFILE"
