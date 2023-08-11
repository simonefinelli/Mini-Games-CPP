cmake_minimum_required(VERSION 3.26)
project(HangmanGame)

set(CMAKE_CXX_STANDARD 17)

# create the executable with all the source files
add_executable(HangmanGame
        src/main.cpp
        src/core.cpp
        src/board.cpp
)

# set the include directories
target_include_directories(HangmanGame PRIVATE ${CMAKE_SOURCE_DIR}/include)
