# Minimum CMake version
cmake_minimum_required(VERSION 3.22)

# Project name and version
project(Vec2D VERSION 1.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)

# Set the include directory for header files
include_directories(include)

# Create an executable that uses the static library
add_executable(Vec2D
        src/main.cpp
        src/vec2D_utils.cpp
        src/Vec2D.cpp
)

# Library Creation =========================================================== #

# Set the base output directory for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/shared")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # runtime output for executables (if any)

# List source files
set(SOURCES
    src/Vec2D.cpp
    src/vec2D_utils.cpp
)

# # Create the static library
# add_library(Vec2DStatic STATIC ${SOURCES})
# set_target_properties(Vec2DStatic PROPERTIES
#     OUTPUT_NAME "Vec2D"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
# )

# Create the shared library
add_library(Vec2DShared SHARED ${SOURCES})
set_target_properties(Vec2DShared PROPERTIES
    OUTPUT_NAME "Vec2D"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
)

# Position Independent Code (PIC) is required for shared libraries or static included in shared library
# target_compile_options(Vec2DStatic PRIVATE -fPIC)
target_compile_options(Vec2DShared PRIVATE -fPIC)

# Testing ==================================================================== #

# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create a test executable
add_executable(TestVec2D
    tests/test_vec2D.cpp
)

# Link GoogleTest to the test executable
target_link_libraries(TestVec2D
    Vec2DShared  # or Vec2DStatic
    GTest::GTest
    GTest::Main
    pthread  # required by GoogleTest
)

# Register the test executable with CTest
add_test(NAME Vec2D COMMAND TestVec2D)

# Add a flag to run tests after build
option(RUN_TESTS "Automatically run tests after build" ON)

# Automatically run tests after building TestVec2D if RUN_TESTS is ON
if(RUN_TESTS)
    add_custom_command(
        TARGET TestVec2D
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
        COMMENT "Running tests after build"
    )
endif()

