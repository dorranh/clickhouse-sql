# clickhouse-sql

> 🚧 Warning: This project is still in a very early state!

Unofficial Python bindings to ClickHouse's SQL parser.

## Description

This project exposes Python bindings to [ClickHouse's](https://clickhouse.com)
SQL parsing library along with a few minimal helpers. Use it to parse and
analyze Clickhouse SQL queries when other parsers can't quite keep up with the
breadth of ClickHouse's SQL dialect.

Note that this is more of a side project at the moment, and for most simple
cases you should probably be using a more generic library like
[`sqlglot`](https://github.com/tobymao/sqlglot).

## Installation

I've not yet gotten around to publishing a wheel to PyPI. In the meantime you
can build and install the project following the developer guide
[below](#development).

## Getting started

### Parsing

To parse a query:

```python
from clickhouse_sql import parse_query, IAST

ast: IAST = parse_query("SELECT * FROM my_table")
```

The resulting object is the root node of the AST parsed from the query.

### Inspection

Concrete types have a variety of methods available for inspection (note that the
current set is quite limited compared to the full ClickHouse API).

```python
ast = parse_query("CREATE TABLE foo ON CLUSTER 'foobar' (a String) ORDER BY a")

print(ast.getCluster()) # returns 'foobar'
```

### Search / traversals

To search for nodes of a specific type:

```python
from clickhouse_sql.helpers import find_all
from clickhouse_sql import nodes


ast = parse_query("SELECT * FROM my_db.my_table WHERE foo='bar'")

matches = find_all(ast, clickhouse_sql.ASTTableIdentifier)
```

## Development

### System dependencies

Linux or MacOS with the following installed:

* [Nix](https://nixos.org/download/)
  * I personally use the [Determine Systems Nix
    installer](https://determinate.systems/nix-installer/).
* Nix Flakes [enabled](https://nixos.wiki/wiki/Flakes)

### Building the project

First, enter a Nix shell. All subsequent commands assume you are running them
within a Nix shell.

```shell
$ nix develop
```

This project includes a `Justfile` to simplify running its various build
commands.

When first checking out the project, you will need to fetch the ClickHouse
sources:

```shell
$ just fetch-clickhouse # This is slow :(
```

Then, to build the project (produces a single-platform Python wheel in
`./dist`):

```shell
$ just build
```

To create a local Python virtual environment for development / testing:

```shell
# Builds and installs this project to .venv
$ just install
```

And to clean build outputs:

```shell
$ just clean
```

An optionally to clean the local checkout of ClickHouse:

```shell
$ just clean-clickhouse
```

### Build notes

- Avoid adding SDK/libc++ include paths or `-nostdinc++` flags globally in
  `CMakeLists.txt`. This can leak into the ClickHouse build and cause missing
  C standard types (e.g., `size_t`) on macOS. Keep these flags scoped to the
  `_clickhouse_sql` target only.

## License

This project is licensed under the MIT License.

It depends on [`ClickHouse`](https://github.com/ClickHouse/ClickHouse), which is
licensed under the Apache License 2.0. See LICENSE-APACHE for details.****
