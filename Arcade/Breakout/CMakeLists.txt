cmake_minimum_required(VERSION 3.22)
project(Breakout)

# C++ Version
set(CMAKE_CXX_STANDARD 20)

# Dependencies =============================================================== #
# Vec2D library (shared): set build and include paths
set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/include")
set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/build/Release/lib/shared")
message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# Shapes library (shared): set build and include paths
set(SHAPES_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Shapes/include")
set(SHAPES_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Shapes/build/Release/lib/shared")
message("SHAPES_LIB_DIR is set to: ${SHAPES_LIB_DIR}")

# Find SDL2 package
find_package(SDL2 REQUIRED)
# Dependencies - End ========================================================= #

# Add main executable (the game, for example)
add_executable(Breakout
    src/main.cpp
    graphics/Color.cpp
    graphics/ScreenBuffer.cpp
    graphics/Screen.cpp
    graphics/graphics_utils.cpp
)

# Set the include directories for the main executable
target_include_directories(Breakout PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/graphics
)

# Link SDL2 to the target
target_link_libraries(Breakout PRIVATE ${SDL2_LIBRARIES})
# Link to the Vec2D static library and header
target_include_directories(Breakout PRIVATE ${VEC2D_INCLUDE_DIR})
target_link_libraries(Breakout PRIVATE ${VEC2D_LIB_DIR}/libVec2D.so)
# Link to the Shapes static library and header
target_include_directories(Breakout PRIVATE ${SHAPES_INCLUDE_DIR})
target_link_libraries(Breakout PRIVATE ${SHAPES_LIB_DIR}/libShapes.so)
