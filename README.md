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

## Build

The simulator depends on g++ (C++11), flex, bison, pthreads, libm and
libfl. Compile the engine and produce the `evac` binary:

```bash
cd Simulation
make
```

## Run

Invoke the simulator with a scenario:

```bash
./evac path/to/scenario.slang
```

Sample scenarios and datasets reside in `Simulation/boise`. For example:

```bash
./evac boise/boise.slang
```

Results from prior experiments and plotting scripts are in
`Simulation/results`. Other scenario sets, such as
`Simulation/topologyTestProbSet`, support additional experiments.

