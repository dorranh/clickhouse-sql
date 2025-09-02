# Create the static library (no need for project() in subdirectory)
add_library(dummy_lib STATIC
    DummyLib.cpp
)

# Set C++ standard
target_compile_features(dummy_lib PUBLIC cxx_std_17)

# Set include directories
target_include_directories(dummy_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Note: Install rules are not needed for subdirectory builds
