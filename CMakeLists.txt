#####################################################################
# Global build config
#####################################################################
cmake_minimum_required(VERSION 3.15...3.27)
project(clickhouse_sql VERSION "0.0.1")

# Note: This build must be run from within the Nix development shell
# The Nix shell provides the correct LLVM toolchain that ClickHouse expects
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

include(litgen_cmake/litgen_cmake.cmake)

#####################################################################
# ClickHouse integration via find_package
#####################################################################

# Add ClickHouse source directory to CMAKE_PREFIX_PATH so find_package can find it
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tmp/ClickHouse")

# Find ClickHouse package (uses our custom ClickHouseConfig.cmake)
find_package(ClickHouse REQUIRED)

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
    # Allow C++23 extensions since ClickHouse uses them (uz suffix literals)
    -Wno-c++23-extensions
    # Force use of Nix libc++ headers to avoid Apple system header conflicts
    -nostdinc++
)

# Add system headers BEFORE any transitive includes to ensure proper header resolution
target_include_directories(_clickhouse_sql SYSTEM BEFORE PRIVATE
    # Include system C headers first (for fundamental types like int32_t, ldiv_t, etc.)
    /nix/store/zm6nfi7l8yq7s0i3m52pxj00nr3n76j5-apple-sdk-15.2/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
    # Then include ClickHouse's libc++ headers (which depend on the C headers above)
    /nix/store/vkdffdlbi5yfdkl50fwc07v33h5z4qkb-libcxx-19.1.7-dev/include/c++/v1
)

# Add preprocessor definitions for ClickHouse and nanobind compatibility
target_compile_definitions(_clickhouse_sql PRIVATE
    _XOPEN_SOURCE=700     # Required for ucontext routines on macOS
    _DARWIN_C_SOURCE=1    # Enable Darwin/macOS specific features like NSIG
    _BSD_SOURCE=1         # Required for BSD-specific features
    _DEFAULT_SOURCE=1     # Enable default set of features
    _GNU_SOURCE=1         # Enable GNU extensions (may be needed for some ClickHouse code)
)

# Now we can directly use ClickHouse targets!
# No need for imported targets or manual library collection.
# CMake will handle all dependencies automatically.

# Link against the ClickHouse targets using proper CMake target linking
# Now we can directly link to the ClickHouse target - much cleaner!
target_link_libraries(_clickhouse_sql
    PRIVATE
    dummy_lib
    ${CLICKHOUSE_LIBRARIES}
)

#     # System libraries that ClickHouse might need
#     pthread
#     dl
#     m
#     # macOS frameworks
#     "-framework CoreFoundation"
#     "-framework Security"
#     "-framework SystemConfiguration"
# )

# Include dummy library headers and ClickHouse headers
target_include_directories(_clickhouse_sql PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DummyLib
    # ClickHouse source headers
    ${CLICKHOUSE_SOURCE_DIR}/src
    ${CLICKHOUSE_SOURCE_DIR}/base
)

# Set up the module with litgen for the dummy library
litgen_setup_module(
    dummy_lib           # The dummy library we're binding to
    _clickhouse_sql      # The native python module name
    clickhouse_sql      # The python wrapper name
    ${CMAKE_CURRENT_SOURCE_DIR}/_stubs  # Output path for stubs
)
