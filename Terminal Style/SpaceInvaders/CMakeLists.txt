cmake_minimum_required(VERSION 3.22)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 17)

# create the executable with all the source files

add_executable(SpaceInvaders
        src/main.cpp
        src/gui.cpp
        src/spaceship.cpp
        src/score.cpp
        src/battlefield.cpp
        src/core.cpp
        src/utils.cpp
)

# set the include directories
target_include_directories(SpaceInvaders PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SpaceInvaders -lncurses)
