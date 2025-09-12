# Evacuation Planning Research

This repository collects code and documents for studying large-scale
evacuation planning. A C++ simulator models traffic flow and agent
behavior across road networks described in a custom scenario language,
Slang.

## Directory Map

- Simulation/ - C++ simulation engine and experiment assets.
- Slang/ - LaTeX sources for the Slang scenario language reference.
- Paper/ - Drafts and figures for the main research paper.
- Papers/ - Reference literature.
- Notes/ - Project notes.

## Build (Bazel)

This repo now builds with Bazel. A minimal setup is included (Bzlmod via
`MODULE.bazel`). Dependencies used by the simulator are generated from the
checked‑in Flex/Bison grammars.

Build the simulator:

```bash
bazel build //Simulation:evac
```

Optional: enable AddressSanitizer for debugging:

```bash
bazel build --config=asan //Simulation:evac
```

## Run

Use the run wrapper to ensure the `outputs/` directory exists and execute the
simulator with a scenario file:

```bash
bazel run //Simulation:evac_run -- Simulation/slang/highway.slang
# or try the provided 4x4 grid scenario
bazel run //Simulation:evac_run -- Simulation/slang/minigrid.slang
```

The wrapper sets the working directory to the workspace root and creates
`outputs/` automatically. If you prefer to run the binary directly, create the
directory first and pass the scenario path:

```bash
mkdir -p outputs
bazel run //Simulation:evac -- Simulation/slang/highway.slang
```

Results are written to `outputs/<CityName>Final.txt` (drawable format with
edges, nodes, probabilities, and agent routes). Historical results and plotting
scripts remain under `Simulation/results`.

## Test (CI/Local)

An end‑to‑end integration test runs the simulator on a small 4×4 grid and
asserts the drawable output is produced:

```bash
bazel test //Simulation:evac_minigrid_it
```

## Visualization (GIF)

For hermetic, Bazel-native artifacts (preferred for CI) you can build the
drawable and an animated GIF for the provided scenarios. These are declared
outputs and will be written under `bazel-bin/Simulation/`.

- Minigrid (4×4 grid):

```bash
bazel build //Simulation:drawable_minigrid
bazel build //Simulation:gif_minigrid
# Artifacts:
#   bazel-bin/Simulation/minigridFinal.txt
#   bazel-bin/Simulation/minigrid_anim.gif
```

- Highway:

```bash
bazel build //Simulation:drawable_highway
bazel build //Simulation:gif_highway
# Artifacts:
#   bazel-bin/Simulation/highwayFinal.txt
#   bazel-bin/Simulation/highway_anim.gif
```

Notes:
- The renderer is a small homebrewed script (`Simulation/tools/viz_gif.py`) that
  draws the network and agents and overlays a progress bar across the bottom of
  the frames to highlight start/end and progress through the simulation.
- It requires Pillow; if missing, install with `pip3 install --user Pillow`.
- The simulator writes its drawable to a directory controlled by
  `EVAC_OUTPUT_DIR` (set automatically by the Bazel rule) for hermetic build
  operation.
