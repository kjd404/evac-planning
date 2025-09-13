---
title: Evacuation Planning Research
---

# Evacuation Planning Research (Public Artifact)

This site presents a cleaned, buildable artifact of graduate research on
evolving evacuation strategies for urban networks. It includes a C++ simulator
with a small scenario language (SLang), and a curated set of animations.

If you’re looking for the code and details, the repository root contains the
full source and LaTeX materials.

## Paper

- View the paper: [paper.pdf](./paper.pdf)

## Demos (Boise)

Population series (60k variants):

![Boise 60k 10%](boise/boise60k10p_anim.gif)
![Boise 60k 20%](boise/boise60k20p_anim.gif)
![Boise 60k 30%](boise/boise60k30p_anim.gif)
![Boise 60k 40%](boise/boise60k40p_anim.gif)
![Boise 60k 50%](boise/boise60k50p_anim.gif)
![Boise 60k 60%](boise/boise60k60p_anim.gif)
![Boise 60k 70%](boise/boise60k70p_anim.gif)
![Boise 60k 80%](boise/boise60k80p_anim.gif)
![Boise 60k 90%](boise/boise60k90p_anim.gif)
![Boise 60k 100%](boise/boise60k100p_anim.gif)

Capacity and safe-to-danger variants:

![Boise 60k 10% + 40% cap](boise/boise60k10p40cp_anim.gif)
![Boise 60k 10% + 40% cap (plain)](boise/boise60k10p40cp_plain_anim.gif)
![Boise 60k 10% (safe-to-danger)](boise/boise60k10ps2d_anim.gif)
![Boise 60k 10% + 40% cap (safe-to-danger)](boise/boise60k10p40cp_s2d_anim.gif)

## Build & Run

Build the simulator (Bazel, C++11, Flex/Bison invoked via Bazel):

```bash
bazel build //Simulation:evac
```

Run on a provided scenario (writes `outputs/<CityName>Final.txt`):

```bash
bazel run //Simulation:evac_run -- Simulation/slang/highway.slang
```

Hermetic demo artifacts (preferred for presentation; Pillow required for GIFs):

```bash
# Drawable only
bazel build //Simulation:drawable_minigrid
bazel build //Simulation:drawable_highway

# Animated GIFs (pip3 install --user Pillow)
bazel build //Simulation:gif_minigrid
bazel build //Simulation:gif_highway
```

## Notes

- Historical figures under `Simulation/results/` and `Paper/` include some PNGs
  that are not easily reproducible; they are preserved as-is for reference.
- The simulator code targets C++11 and builds with Bazel + Bzlmod.
