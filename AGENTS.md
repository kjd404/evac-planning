# Repository Guidelines

## C++ Style
- Format all C++ code with `clang-format`.
- Target the C++11 standard for all builds.

## Commit Messages
- Use imperative mood in the subject line (e.g., "add feature").
- Keep the subject under 50 characters.
- Separate the subject from the body with a blank line.
- Wrap body lines at 72 characters.

## Directory Structure
- `Simulation/` – C++ simulation engine and build files.
- `Slang/` – LaTeX sources for the scenario language documentation.
- `Paper/` – Drafts and resources for the main research paper.
- `Notes/` – Project notes and planning documents.

## Build Tooling
- Bazel (Bzlmod enabled via `MODULE.bazel`).
- Flex/Bison are invoked by Bazel to generate the lexer/parser from sources.
- Python 3 is required only for visualization (Pillow).

## Mandatory Checks
- Build succeeds:

  ```bash
  bazel build //Simulation:evac
  ```

- Optional debug build:

  ```bash
  bazel build --config=asan //Simulation:evac
  ```

- End‑to‑end run on a scenario (produces `outputs/<CityName>Final.txt`):

  ```bash
  bazel run //Simulation:evac_run -- Simulation/slang/highway.slang
  ```

## Hermetic artifacts (preferred for CI)
- Drawable files (no workspace writes):

  ```bash
  bazel build //Simulation:drawable_minigrid
  # bazel-bin/Simulation/minigridFinal.txt
  bazel build //Simulation:drawable_highway
  # bazel-bin/Simulation/highwayFinal.txt
  ```

- Animated GIFs (requires Pillow `pip3 install --user Pillow`):

  ```bash
  bazel build //Simulation:gif_minigrid
  # bazel-bin/Simulation/minigrid_anim.gif
  bazel build //Simulation:gif_highway
  # bazel-bin/Simulation/highway_anim.gif
  ```

## Developer Tips
- Use `//Simulation:evac_run` for quick local runs; for CI use the
  hermetic `drawable_*` and `gif_*` targets.
- The simulator honors `EVAC_OUTPUT_DIR` (set by the hermetic rules) to specify
  where drawable files are written.
- The visualization script is intentionally simple (Pillow) to be easy to
  maintain; pass `--edgewidth prob|const`, `--trails`, and `--fps/--duration`
  to tune output.

Future tests can be added under Bazel `sh_test` or `py_test` targets.
