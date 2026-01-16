# ClickHouse revision to use. Note that the build may break when changing
# this since it may be sensitive to the LLVM version, etc.
CLICKHOUSE_REVISION := "0a8bf8ff305fe56974a42de65cf8ec8b3e497ee6"
NANOBIND_REVISION := "116e098cfa96effca2a54e32e0ce5b93abe25393"


# create local virtual environment
install-dev:
  uv sync --no-install-project

# install to local virtual environment
install: install-dev
  uv pip install . --verbose

# build Python wheel
build: install-dev
  # Disabling build isolation to allow for caching of the ClickHouse build
  uv build --no-build-isolation --wheel --verbose

# build using cibuildwheel (for publishing)
build-ci: install-dev
  uv run --only-dev python -m cibuildwheel --output-dir wheelhouse

# download nanobind source
fetch-nanobind:
  #!/usr/bin/env sh
  if [ ! -d "tmp/nanobind" ]; then
    git clone --revision {{NANOBIND_REVISION}} -j8 --depth 1 --recursive --shallow-submodules https://github.com/wjakob/nanobind.git tmp/nanobind
  else
    echo "Directory tmp/nanobind already exists. Skipping clone."
  fi

# download Clickhouse source
fetch-clickhouse:
  #!/usr/bin/env sh
  if [ ! -d "tmp/ClickHouse" ]; then
    git clone --revision {{CLICKHOUSE_REVISION}} -j8 --depth 1 --recursive --shallow-submodules https://github.com/ClickHouse/ClickHouse.git tmp/ClickHouse
    echo "Applying patches..."
    cd tmp/ClickHouse
    git apply ../../patches/clickhouse-preload.patch
    git apply ../../patches/clickhouse-config.patch
    git apply ../../patches/clickhouse-path-fix.patch
    echo "Patches applied successfully."
    cd ../..
  else
    echo "Directory tmp/ClickHouse already exists. Skipping clone."
  fi

# clean ClickHouse source
clean-clickhouse:
  rm -rf tmp

# clean build files
clean:
  rm -rf .venv
  rm -rf _skbuild
  rm -rf dist
