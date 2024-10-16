cmake_minimum_required(VERSION 3.22)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)

add_executable(Breakout
        ./src/main.cpp
        ./utils/Vec2D.cpp
)

# set the include directories
target_include_directories(Breakout PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/utils
)

