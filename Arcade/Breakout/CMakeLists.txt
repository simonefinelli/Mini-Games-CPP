cmake_minimum_required(VERSION 3.22)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)

# Vec2D library: set build and include paths
set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/include")
set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../libs/Vec2D/build/Release/lib/static")
message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# Add main executable (the game, for example)
add_executable(Breakout
    src/main.cpp
    graphics/Color.cpp
    graphics/ScreenBuffer.cpp
    graphics/Screen.cpp
    shapes/Line2D.cpp
    shapes/Shape2D.cpp
    shapes/Triangle2D.cpp
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Set the include directories for the main executable
target_include_directories(Breakout PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/graphics
    ${CMAKE_SOURCE_DIR}/shapes
)

# Link SDL2 to the target
target_link_libraries(Breakout PRIVATE ${SDL2_LIBRARIES})

# Link to the Vec2D static library and header
target_include_directories(Breakout PRIVATE ${VEC2D_INCLUDE_DIR})
target_link_libraries(Breakout PRIVATE ${VEC2D_LIB_DIR}/libVec2D.a)
