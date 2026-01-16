# AGENTS.md

## Project description

- Python bindings to a C++ lib that wraps / reexports the AST library for ClickHouse
- Build uses CMake + Nanobind + scikit-build-core with dev env provided by a Nix shell

## Setup commands

- All commands must be run in a Nix shell. Enter one if you aren't already in one: `nix develop`
- ClickHouse source must be fetched one time (it is very slow to fetch). Use `just fetch-clickhouse`.
- You can build with `just build` or `just install-dev`. The latter can be used when you need to run tests.

## Code style

- C++ idiomatic and kept to minimum
- Complex logic done at high-level in Python as much as possible
- Use functional patterns where possible
- New utilities must be integrated in the top-level Justfile
- Write tests wherever possible
- Favor high-level tests in Python to C++ tests
