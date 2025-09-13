---
title: Evacuation Planning Research
---

# Evacuation Planning Research (Public Artifact)

This site preserves and presents a small body of graduate research on
evolving evacuation strategies for urban road networks. The focus is on making
the original results visible and understandable, with minimal changes to the
code or data. The repository contains the simulator, scenarios, figures, and a
PDF of the paper.

- Read the paper: [paper.pdf](./paper.pdf)

## Research Overview

- Problem: route a city’s population toward safety during a disaster while
  accounting for congestion, capacity limits, and imperfect compliance.
- Representation: at every intersection, a static probability distribution over
  outgoing roads (plus “stay”) encodes guidance; probabilities at a node sum to 1.
- Objective: maximize aggregate safety of all agents by the end of a fixed
  horizon. Safety is a per‑node value (e.g., distance from danger, elevation,
  designated safe regions).
- Traffic model: macroscopic agent groups with link travel times computed using
  a BPR‑style function: free‑flow time scaled by a congestion term depending on
  current flow and link capacity.
- Optimization: an Evolution Strategy (real‑valued genome) evolves the per‑node
  distributions; mutation perturbs node distributions and renormalizes; optional
  crossover swaps node‑level distributions between parents.
- Robustness: the probabilistic encoding tolerates some “disobedience” (agents
  not following guidance exactly) and can be re‑optimized quickly after topology
  or safety changes by seeding from prior solutions.

## Boise Example (What the GIFs Show)

To make the results tangible, we animated drawables from experiments on a
Boise, ID road network used during the research. Each animation interpolates
agent motion along routes and overlays simple visual cues:

- Edge width: proportional to evolved routing probability on that edge.
- Node color: reflects safety (safer nodes are greener/bluer; unsafe are redder).
- Dots (agents): size scales with group size; trails show recent movement.
- Progress bar: indicates time progression through the simulation horizon.

These are qualitative visualizations intended to communicate routing patterns,
congestion effects, and adaptation. Exact timings in the historical drawables
are sometimes coarse; the animations still reflect the evolved distributions.

### Population Series (60k baseline, 10%–100%)

The following GIFs vary the population scale while keeping network and safety
conditions constant. As population rises, congestion increases, and the evolved
probabilities redirect more flow to alternate corridors to maintain safety.

![Boise 60k 10%](boise/boise60k10p_anim.gif)
_10% of 60k population_
![Boise 60k 20%](boise/boise60k20p_anim.gif)
_20% of 60k population_
![Boise 60k 30%](boise/boise60k30p_anim.gif)
_30% of 60k population_
![Boise 60k 40%](boise/boise60k40p_anim.gif)
_40% of 60k population_
![Boise 60k 50%](boise/boise60k50p_anim.gif)
_50% of 60k population_
![Boise 60k 60%](boise/boise60k60p_anim.gif)
_60% of 60k population_
![Boise 60k 70%](boise/boise60k70p_anim.gif)
_70% of 60k population_
![Boise 60k 80%](boise/boise60k80p_anim.gif)
_80% of 60k population_
![Boise 60k 90%](boise/boise60k90p_anim.gif)
_90% of 60k population_
![Boise 60k 100%](boise/boise60k100p_anim.gif)
_100% of 60k population_

### Capacity & Initialization Variants

These variants illustrate adaptation to degraded infrastructure and different
initializations of the optimizer.

- 40% capacity: models reduced road capacity (e.g., closures, damage); evolved
  distributions route around bottlenecks while steering toward safer areas.
- Safe‑to‑danger (S2D) initialization: seeds probabilities by “filling from the
  safest zones outward”, often providing faster convergence and distinct flows.

![Boise 60k 10% + 40% cap](boise/boise60k10p40cp_anim.gif)
_10% pop + 40% capacity (evolved)_
![Boise 60k 10% + 40% cap (plain init)](boise/boise60k10p40cp_plain_anim.gif)
_10% pop + 40% cap (plain init)_
![Boise 60k 10% (S2D init)](boise/boise60k10ps2d_anim.gif)
_10% pop (safe‑to‑danger init)_
![Boise 60k 10% + 40% cap (S2D init)](boise/boise60k10p40cp_s2d_anim.gif)
_10% pop + 40% cap (safe‑to‑danger init)_

## Notes & Provenance

- This page presents a curated subset of the historical outputs used during the
  research. Some static figures in the repository are not easily reproducible
  on current systems; they are preserved as‑is.
- The code and scenarios are available in the repository for those who wish to
  explore further or reproduce artifacts locally; see the README there.
