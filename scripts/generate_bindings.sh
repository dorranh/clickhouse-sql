#!/bin/bash
# generate_bindings.sh - Generates Pybind11 bindings using Binder

set -e

# Paths (Modify these based on your setup)
BINDER_PATH=~/binder/build/source/binder
CLICKHOUSE_INCLUDE=/path/to/ClickHouse/includes
CLICKHOUSE_PARSER_HEADER=/path/to/ClickHouse/src/Parsers/IAST.h
OUTPUT_DIR=bindings_output

# Ensure output directory exists
mkdir -p $OUTPUT_DIR

# Run Binder to generate C++ bindings
$BINDER_PATH \
    --root-module clickhouse_parser \
    --prefix $OUTPUT_DIR \
    --bind "DB::IAST" \
    $CLICKHOUSE_PARSER_HEADER \
    -- -std=c++17 -I$CLICKHOUSE_INCLUDE

echo "Bindings generated successfully in $OUTPUT_DIR"

