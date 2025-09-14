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
- `simulation/` – C++ simulation engine and build files.
- `slang/` – LaTeX sources for the scenario language documentation.
- `paper/` – Drafts and resources for the main research paper.

## Build Tooling
- Bazel (Bzlmod enabled via `MODULE.bazel`).
- Lexer/parser C sources are checked in under `simulation/generated/` for
  reproducible builds; regenerating with Flex/Bison is optional.
- Python 3 is required only for visualization (Pillow).

## Mandatory Checks
- Build succeeds:

  ```bash
  bazel build //simulation:evac
  ```

- Optional debug build:

  ```bash
  bazel build --config=asan //simulation:evac
  ```

- End‑to‑end run on a scenario (produces `outputs/<CityName>Final.txt`):

  ```bash
  bazel run //simulation:evac_run -- simulation/slang/highway.slang
  ```

## Hermetic artifacts (preferred for CI)
- Drawable files (no workspace writes):

  ```bash
  bazel build //simulation:drawable_minigrid
  # bazel-bin/simulation/minigridFinal.txt
  bazel build //simulation:drawable_highway
  # bazel-bin/simulation/highwayFinal.txt
  ```

- Animated GIFs (requires Pillow `pip3 install --user Pillow`):

  ```bash
  bazel build //simulation:gif_minigrid
  # bazel-bin/simulation/minigrid_anim.gif
  bazel build //simulation:gif_highway
  # bazel-bin/simulation/highway_anim.gif
  ```

## Developer Tips
- Use `//simulation:evac_run` for quick local runs; for CI use the
  hermetic `drawable_*` and `gif_*` targets.
- The simulator honors `EVAC_OUTPUT_DIR` (set by the hermetic rules) to specify
  where drawable files are written.
- The visualization script is intentionally simple (Pillow) to be easy to
  maintain; pass `--edgewidth prob|const`, `--trails`, and `--fps/--duration`
  to tune output.

Future tests can be added under Bazel `sh_test` or `py_test` targets.
