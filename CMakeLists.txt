cat <<EOL > CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(clickhouse_parser_bindings)

find_package(Python3 REQUIRED COMPONENTS Development)
find_package(pybind11 REQUIRED)

include_directories(${CLICKHOUSE_INCLUDE})

pybind11_add_module(clickhouse_parser bindings_output/clickhouse_parser.cpp)
EOL

echo "CMakeLists.txt generated."
