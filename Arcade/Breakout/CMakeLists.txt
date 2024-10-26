cmake_minimum_required(VERSION 3.22)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)

# Add main executable (the game, for example)
add_executable(Breakout
    ./src/main.cpp
    ./utils/Vec2D.cpp
    ./utils/vec2D_utils.cpp
    ./graphics/Color.cpp
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Set the include directories for the main executable
target_include_directories(Breakout PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/graphics
)

# Enable testing with CTest
enable_testing()

# Add a separate test executable
add_executable(Vec2DTests
    ./utils/tests/test_vec2D.cpp
    ./utils/Vec2D.cpp
    ./utils/vec2D_utils.cpp
)

# Set the include directories for the main executable
target_include_directories(Vec2DTests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/utils
)

# Link SDL2 to the target
target_link_libraries(Breakout PRIVATE ${SDL2_LIBRARIES})

# Link GoogleTest to the test executable
target_link_libraries(Vec2DTests
    GTest::GTest
    GTest::Main
    pthread  # ensure pthread is linked (required by GoogleTest)
)

# Register the test executable with CTest
add_test(NAME Vec2DTests COMMAND Vec2DTests)

# Optional: Add a flag to run tests after build
option(RUN_TESTS "Automatically run tests after build" ON)

if(RUN_TESTS)
    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS Vec2DTests
    )
    add_dependencies(run_tests Vec2DTests)  # ensure tests are built before running
endif()