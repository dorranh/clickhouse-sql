from setuptools import setup, Extension
import pybind11

ext = Extension(
    "clickhouse_parser",
    sources=["bindings_output/clickhouse_parser.cpp"],
    include_dirs=[pybind11.get_include(), "${CLICKHOUSE_INCLUDE}"],
    language="c++",
    extra_compile_args=["-std=c++17"],
)

setup(
    name="clickhouse_parser",
    version="0.1",
    ext_modules=[ext],
)
