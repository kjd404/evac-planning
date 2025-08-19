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

## Required Dependencies
- `g++` with C++11 support
- `flex`
- `bison`
- Libraries for pthreads, math (`-lm`), and Flex (`libfl`)

## Mandatory Checks
Before committing, ensure the project builds:

```bash
cd Simulation && make
```

Once tests are available, run:

```bash
make test
```

