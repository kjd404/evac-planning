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
- `Papers/` – Reference papers and related literature.
- `Notes/` – Project notes and planning documents.

## Build Tooling
- Bazel (Bzlmod enabled via `MODULE.bazel`)
- Flex/Bison are invoked by Bazel to generate the lexer/parser from sources.

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

Future tests can be wired under Bazel test targets.
