# clickhouse-sql

> Warning! This project is a WIP and is not in a functioning state!

Python bindings to ClickHouse's SQL parser.

# Motivation

ClickHouse's SQL dialect is quite complex and strays pretty far from ANSI SQL,
making it is hard to parse with standard tools. This project is intended to
expose a Python interface to ClickHouse's SQL parser to support static analysis
and other use cases.

# TODO:

- [ ] Nix flake
- [ ] Compilation for ClickHouse parser lib
- [ ] Functional binding generation (goal is for read only bindings for
      starters)
