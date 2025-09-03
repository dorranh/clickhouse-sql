CLICKHOUSE_REVISION := "0a8bf8ff305fe56974a42de65cf8ec8b3e497ee6"

# install dev dependencies
install-dev:
  uv sync --no-install-project

# install to local virtual environment
install: install-dev
  uv pip install . --verbose

# build Python wheel
build:
  uv build

# generate Python bindings
generate-bindings:
  uv run python scripts/litgen-generate.py

# download Clickhouse source
fetch-clickhouse:
  #!/usr/bin/env sh
  if [ ! -d "tmp/ClickHouse" ]; then
    git clone --revision {{CLICKHOUSE_REVISION}} -j8 --depth 1 --recursive --shallow-submodules https://github.com/ClickHouse/ClickHouse.git tmp/ClickHouse
  else
    echo "Directory tmp/ClickHouse already exists. Skipping clone."
  fi

# clean build files
clean:
  rm -rf .venv
  rm -rf _skbuild
  rm -rf dist

# clean ClickHouse source
clean-clickhouse:
  rm -rf tmp