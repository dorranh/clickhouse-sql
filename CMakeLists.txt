#####################################################################
# Global build config
#####################################################################
cmake_minimum_required(VERSION 3.15...3.27)
project(clickhouse_sql VERSION "0.0.1")

# Note: This build must be run from within the Nix development shell
# The Nix shell provides the correct LLVM toolchain that ClickHouse expects
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Note: We don't set global CXXFLAGS/LDFLAGS here because ClickHouse external project
# needs to use its own compiler settings. Instead, we'll set these flags specifically
# for our Python module target below.

include(FetchContent)
include(ExternalProject)
include(litgen_cmake/litgen_cmake.cmake)

#####################################################################
# Integrated ClickHouse build
#####################################################################

# # Set ClickHouse build directory
set(CLICKHOUSE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tmp/ClickHouse)
set(CLICKHOUSE_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/clickhouse-build)

ExternalProject_Add(clickhouse_external
    SOURCE_DIR ${CLICKHOUSE_SOURCE_DIR}
    BINARY_DIR ${CLICKHOUSE_BUILD_DIR}
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        # ClickHouse should use the Nix clang from the shell but with its own libc++ settings
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        # -DCMAKE_C_COMPILER=${CMAKE_CXX_COMPILER} I can likely remove this, but leaving for now just in case. The generated value is incorrect though.
        -DENABLE_LIBRARIES=OFF
        # TODO: Some of these flags are not necessary:
        # CLICKHOUSE_SPLIT_BINARY
        # ENABLE_CLICKHOUSE_BENCHMARK
        # ENABLE_CLICKHOUSE_CLIENT
        # ENABLE_CLICKHOUSE_COMPRESSOR
        # ENABLE_CLICKHOUSE_COPIER
        # ENABLE_CLICKHOUSE_DISKS
        # ENABLE_CLICKHOUSE_EXTRACT_FROM_CONFIG
        # ENABLE_CLICKHOUSE_FORMAT
        # ENABLE_CLICKHOUSE_INSTALL
        # ENABLE_CLICKHOUSE_LOCAL
        # ENABLE_CLICKHOUSE_OBFUSCATOR
        # ENABLE_CLICKHOUSE_SERVER
        # ENABLE_CLICKHOUSE_STATIC_FILES_DISK_UPLOADER
        # ENABLE_CLICKHOUSE_SU
        # ENABLE_PROGRAMS
        -DENABLE_TESTS=OFF
        -DENABLE_BENCHMARKS=OFF
        -DENABLE_UTILS=OFF
        -DENABLE_PROGRAMS=OFF
        -DCLICKHOUSE_SPLIT_BINARY=OFF
        -DENABLE_CLICKHOUSE_ALL=OFF
        -DENABLE_CLICKHOUSE_SERVER=OFF
        -DENABLE_CLICKHOUSE_CLIENT=OFF
        -DENABLE_CLICKHOUSE_LOCAL=OFF
        -DENABLE_CLICKHOUSE_BENCHMARK=OFF
        -DENABLE_CLICKHOUSE_EXTRACT_FROM_CONFIG=OFF
        -DENABLE_CLICKHOUSE_COMPRESSOR=OFF
        -DENABLE_CLICKHOUSE_COPIER=OFF
        -DENABLE_CLICKHOUSE_FORMAT=OFF
        -DENABLE_CLICKHOUSE_OBFUSCATOR=OFF
        -DENABLE_CLICKHOUSE_GIT_IMPORT=OFF
        -DENABLE_CLICKHOUSE_STATIC_FILES_DISK_UPLOADER=OFF
        -DENABLE_CLICKHOUSE_SU=OFF
        -DENABLE_CLICKHOUSE_INSTALL=OFF
        -DENABLE_CLICKHOUSE_DISKS=OFF
        -DENABLE_CLICKHOUSE_KEEPER=OFF
        -DENABLE_CLICKHOUSE_KEEPER_CONVERTER=OFF
        -DENABLE_CLICKHOUSE_SELF_EXTRACTING=OFF
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --target clickhouse_parsers clickhouse_common_io common --parallel
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS
        ${CLICKHOUSE_BUILD_DIR}/src/libclickhouse_parsers.a
        ${CLICKHOUSE_BUILD_DIR}/src/libclickhouse_common_io.a
        ${CLICKHOUSE_BUILD_DIR}/base/libcommon.a
)

# Create imported targets for the ClickHouse libraries
add_library(clickhouse_parsers_lib STATIC IMPORTED)
set_target_properties(clickhouse_parsers_lib PROPERTIES
    IMPORTED_LOCATION ${CLICKHOUSE_BUILD_DIR}/src/libclickhouse_parsers.a
)
add_dependencies(clickhouse_parsers_lib clickhouse_external)

add_library(clickhouse_common_io_lib STATIC IMPORTED)
set_target_properties(clickhouse_common_io_lib PROPERTIES
    IMPORTED_LOCATION ${CLICKHOUSE_BUILD_DIR}/src/libclickhouse_common_io.a
)
add_dependencies(clickhouse_common_io_lib clickhouse_external)

add_library(clickhouse_common_lib STATIC IMPORTED)
set_target_properties(clickhouse_common_lib PROPERTIES
    IMPORTED_LOCATION ${CLICKHOUSE_BUILD_DIR}/base/libcommon.a
)
add_dependencies(clickhouse_common_lib clickhouse_external)

# Set the headers directory. We need this for generating pybind11 bindings
set(CLICKHOUSE_HEADERS_DIR "${CLICKHOUSE_SOURCE_DIR}/src/Parsers" CACHE STRING "Path to ClickHouse headers")
message(STATUS "CLICKHOUSE_HEADERS_DIR set to: ${CLICKHOUSE_HEADERS_DIR}")

#####################################################################
# Dummy library setup
#####################################################################
add_subdirectory(DummyLib)

#####################################################################
# This project
#####################################################################
litgen_find_nanobind()

set(python_module_sources
    _pydef_nanobind/module.cpp
    _pydef_nanobind/nanobind_ClickHouseParsers.cpp
)
nanobind_add_module(_clickhouse_sql ${python_module_sources})

# Ensure we use Nix libc++ headers and avoid Apple system C++ headers
target_compile_options(_clickhouse_sql PRIVATE
    # -stdlib=libc++
    -Wno-unknown-warning-option
    -Wno-error=offsetof-within-non-standard-layout
    # # Fix for Nix libc++ tm struct issue
    # -D_LIBCPP_HAS_NO_VENDOR_AVAILABILITY_ANNOTATIONS
    # -D_LIBCPP_DISABLE_AVAILABILITY
    # Force use of Nix libc++ headers to avoid Apple system header conflicts
    -nostdinc++
    -isystem /nix/store/vkdffdlbi5yfdkl50fwc07v33h5z4qkb-libcxx-19.1.7-dev/include/c++/v1
    # Also include system headers that are needed (like cstddef, cstring, etc.)
    # -isystem /nix/store/zm6nfi7l8yq7s0i3m52pxj00nr3n76j5-apple-sdk-15.2/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
)

# Link against the dummy library for testing
target_link_libraries(_clickhouse_sql
    PRIVATE
    dummy_lib
)

# Also link against Nix libc++ libraries specifically for this target
if(DEFINED ENV{LDFLAGS})
    target_link_options(_clickhouse_sql PRIVATE $ENV{LDFLAGS})
    message(STATUS "Using LDFLAGS for _clickhouse_sql target: $ENV{LDFLAGS}")
endif()

# Include dummy library headers
target_include_directories(_clickhouse_sql PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DummyLib
)

# Set up the module with litgen for the dummy library
litgen_setup_module(
    dummy_lib           # The dummy library we're binding to
    _clickhouse_sql      # The native python module name
    clickhouse_sql      # The python wrapper name
    ${CMAKE_CURRENT_SOURCE_DIR}/_stubs  # Output path for stubs
)
