cmake_minimum_required(VERSION 3.22)
project(Breakout)

# C++ Version
set(CMAKE_CXX_STANDARD 20)

# Dependencies =============================================================== #
# Vec2D library (shared): set build and include paths
set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/include")
set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/build/Release/lib/shared")  # or ".../lib/static"
message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# Shapes library (Shared): set build and include paths
set(SHAPES_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Shapes/include")
set(SHAPES_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Shapes/build/Release/lib/shared")  # or ".../lib/static"
message("SHAPES_LIB_DIR is set to: ${SHAPES_LIB_DIR}")

# Graphics library (Static): set build and include paths
set(GRAPHICS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Graphics/include")
set(GRAPHICS_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Graphics/build/Release/lib/static")  # or ".../lib/shared"
message("GRAPHICS_LIB_DIR is set to: ${GRAPHICS_LIB_DIR}")

# Find SDL2 package
find_package(SDL2 REQUIRED)
# Dependencies - End ========================================================= #

# Add main executable (the game, for example)
add_executable(Breakout
    src/main.cpp
)

# Set the include directories for the main executable
target_include_directories(Breakout PRIVATE 
${CMAKE_SOURCE_DIR}/include
    ${GRAPHICS_INCLUDE_DIR}  # Graphics headers
    ${SHAPES_INCLUDE_DIR}  # Shapes headers
    ${VEC2D_INCLUDE_DIR}  # Vec2D headers
)

target_link_libraries(Breakout PRIVATE
    ${SDL2_LIBRARIES}  # SDL2
    ${GRAPHICS_LIB_DIR}/libGraphics.a  # or ".so"
    ${SHAPES_LIB_DIR}/libShapes.so  # or ".a"
    ${VEC2D_LIB_DIR}/libVec2D.so  # or ".a"
)
