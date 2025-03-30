# Set the shell for commands
set shell := ["bash", "-euxo", "pipefail"]

# Variables (modify as needed)
BINDER := ~/binder/build/source/binder
CLICKHOUSE_INCLUDE := /path/to/ClickHouse/includes
CLICKHOUSE_PARSER_HEADER := /path/to/ClickHouse/src/Parsers/IAST.h
OUTPUT_DIR := bindings_output

# Generate C++ bindings using Binder
gen-bindings:
    mkdir -p {{OUTPUT_DIR}}
    {{BINDER}} \
        --root-module clickhouse_parser \
        --prefix {{OUTPUT_DIR}} \
        --bind "DB::IAST" \
        {{CLICKHOUSE_PARSER_HEADER}} \
        -- -std=c++17 -I{{CLICKHOUSE_INCLUDE}}

# Build the module using CMake
build:
    just gen-bindings
    mkdir -p build
    cd build && cmake ..
    make -j$(nproc)

# Install the Python module
install:
    just build
    pip install .

# Clean up build files
clean:
    rm -rf build {{OUTPUT_DIR}}

# Full rebuild
rebuild:
    just clean
    just install
