cmake_minimum_required(VERSION 3.22)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

# create the executable with all the source files
add_executable(Battleship
        src/main.cpp
        src/ship.cpp
        src/board.cpp
        src/player.cpp
        src/core.cpp
        src/gui.cpp
        src/utils.cpp
)

# set the include directories
target_include_directories(Battleship PRIVATE ${CMAKE_SOURCE_DIR}/include)
