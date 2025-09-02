# Variables (modify as needed)
CLICKHOUSE_REVISION := "0a8bf8ff305fe56974a42de65cf8ec8b3e497ee6"

# Note: All other deps are provided by the Nix flake
install-dev:
  uv sync

install:
  uv pip install . --verbose

build:
  uv build

generate-bindings:
  uv run python scripts/litgen-generate.py

# Fetch Clickhouse source
fetch-clickhouse:
  git clone --revision {{CLICKHOUSE_REVISION}} -j8 --depth 1 --recursive --shallow-submodules https://github.com/ClickHouse/ClickHouse.git tmp/ClickHouse

# Clean up build files
clean:
  rm -rf tmp
  rm -rf .venv
  rm -rf _skbuild
  rm -rf dist