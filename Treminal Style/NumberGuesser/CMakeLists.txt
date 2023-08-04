cmake_minimum_required(VERSION 3.26)
project(NumberGuesser)

set(CMAKE_CXX_STANDARD 17)


# create the executable with all the source files
add_executable(NumberGuesser
        src/gui.cpp
        src/main.cpp
        src/utils.cpp
)

# set the include directories
target_include_directories(NumberGuesser PRIVATE ${CMAKE_SOURCE_DIR}/include)

# To build the project
# mkdir build
# cd build
# cmake ..
# make