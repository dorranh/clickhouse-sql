# clickhouse-sql

> 🚧 Warning! This project is a WIP and is not in a functioning state!

Python bindings to ClickHouse's SQL parser.

## Installation

I've not yet gotten around to publishing a wheel to PyPI. In the meantime you can build and install the project following the
developer guide below.

## Description

This project exposes Python bindings to the ClickHouse's internal SQL parsing
library. Use it to parse and analyze Clickhouse SQL queries when other parsers
can't quite keep up with the breadth of ClickHouse's SQL dialect.

The vision for this project is for it to re-export the internal parsing library from ClickHouse along with a minimal set of stable wrappers.

## Development

### System dependencies

* [Nix](https://nixos.org/download/)
  * I personally use the [Determine Systems Nix installer](https://determinate.systems/nix-installer/).
* Nix Flakes [enabled](https://nixos.wiki/wiki/Flakes)

### Building the project

First, enter a Nix shell. All subsequent commands assume you are running them within a Nix shell.

```shell
$ nix develop
```

This project includes a Justfile to simplify running its various build commands.

To build the project (produces a Python wheel in `./dist`):

```
$ just build
```

To create a local Python virtual environment for development / testing:

```shell
# Creates a virtual env at .venv with dev dependencies
$ just install-dev
# Builds and installs this project to .venv
$ just install
```

And to clean build outputs:

```shell
$ just clean
```

### Re-generating bindings

This project uses [`litgen`](https://github.com/pthom/litgen) to generate Python bindings (using `nanobind`). These bindings and their
associated Python type stubs are checked into the repo under [`./_pydef_nanobind`](./_pydef_nanobind) and [`./_stubs`](./_stubs).

To re-run generation:

```shell
$ just generate-bindings
```

## License

This project is licensed under the MIT License.

It depends on [`ClickHouse`](https://github.com/ClickHouse/ClickHouse), which is licensed under the Apache License 2.0.
See LICENSE-APACHE for details.