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
