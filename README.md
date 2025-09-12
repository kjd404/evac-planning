# Evacuation Planning Research (Public Artifact)

This repository is a public artifact of my graduate research at the University
of Idaho on evolving evacuation strategies for urban networks. The core is a C++
simulator paired with a small domain language (SLang) for defining scenarios.

The research proposes optimizing static routing distributions (node → edge
probabilities) with an Evolution Strategy to maximize safety while accounting
for congestion and variability in traveler behavior. The simulator is a
macroscopic agent model using a BPR-style travel-time link function. A detailed
write‑up appears in the Paper/ directory (see `Paper/Paper.tex`).

Funding and rights: This work was funded by the U.S. National Science
Foundation (NSF) and performed at the University of Idaho (UOI). Copyright and
ownership remain with NSF and UOI; this repository is a public showing of the
research and code for educational and archival purposes.

Modernization note: The goal of this project is to make the original work easy
to build, run, and explore on modern systems with minimal changes to the code
or results. We are introducing small build and tooling updates (e.g., Bazel,
hermetic artifacts, visualization) while preserving the behavior and structure
of the original simulator and scenarios.

## Directory Map

- `Simulation/` – C++ simulation engine, SLang lexer/parser, Bazel targets.
- `Slang/` – LaTeX source of the SLang language reference.
- `Paper/` – Draft of the research paper, figures, and resources.
- `Papers/` – Reference literature and related work.
- `Notes/` – Project notes used during the original research.

## Architecture in Brief

- City as a directed graph (nodes, edges). Link travel time uses
  `freeflow * (1 + b * (c/cmax)^beta)`.
- Agents are grouped and evaluated in a priority queue by arrival time.
- Chromosome encodes per-node distributions over outgoing edges (probabilities
  sum to 1 per node).
- Evolution Strategy (ES+/ES,) optimizes safety (sum over agents) subject to
  traffic dynamics; parameters set via `parameters` in SLang.
- SLang defines city, edges, nodes, agents, parameters, and `run` commands.

## Build (Bazel)

This repo builds with Bazel (Bzlmod via `MODULE.bazel`). Flex/Bison are run by
the build to generate the lexer/parser from sources.

Build the simulator:

```bash
bazel build //Simulation:evac
```

Optional AddressSanitizer for debugging:

```bash
bazel build --config=asan //Simulation:evac
```

## Run

Use the run wrapper to ensure the `outputs/` directory exists and execute the
simulator with a scenario file:

```bash
bazel run //Simulation:evac_run -- Simulation/slang/highway.slang
# or the 4×4 grid scenario
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

A small end‑to‑end integration test runs the simulator on a 4×4 grid and asserts
the drawable is produced:

```bash
bazel test //Simulation:evac_minigrid_it
```

## Visualization (GIF)

For hermetic, Bazel‑native artifacts (preferred for CI) you can build the
drawable and an animated GIF for the provided scenarios. Artifacts are written
to `bazel-bin/Simulation/`.

- Minigrid (4×4 grid):

```bash
# Requires Pillow: pip3 install --user Pillow
bazel build //Simulation:drawable_minigrid
bazel build //Simulation:gif_minigrid
# Artifacts:
#   bazel-bin/Simulation/minigridFinal.txt
#   bazel-bin/Simulation/minigrid_anim.gif
```

- Highway:

```bash
# Requires Pillow: pip3 install --user Pillow
bazel build //Simulation:drawable_highway
bazel build //Simulation:gif_highway
# Artifacts:
#   bazel-bin/Simulation/highwayFinal.txt
#   bazel-bin/Simulation/highway_anim.gif
```

Notes:
- The renderer (Simulation/tools/viz_gif.py) is a small homebrewed script that
  draws the network and agents and overlays a progress bar across the bottom to
  highlight start/end and progress through the simulation. It supports trails,
  edge width by probability, and scaling by group size.
- The simulator honors `EVAC_OUTPUT_DIR` (set by the Bazel rules) when producing
  drawables in hermetic builds.

## Contributing & Modernization

The modernization effort focuses on build/test/visualization and documentation
without altering the original algorithms or data. If you’re exploring the code:
- Prefer hermetic Bazel targets for reproducible outputs.
- Use `--config=asan` for debugging.
- Keep changes small and scoped; aim to preserve behavior.

For code style, build, and test guidelines see `AGENTS.md`.
