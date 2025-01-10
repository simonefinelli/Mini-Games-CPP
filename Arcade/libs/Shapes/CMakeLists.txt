# # Minimum CMake version
# cmake_minimum_required(VERSION 3.22)

# # Project name and version
# project(Shapes VERSION 1.0)

# # C++ Version
# set(CMAKE_CXX_STANDARD 20)

# # Set the include directory for header files
# include_directories(include)

# # Vec2D library: set build and include paths
# set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/include")
# set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/build/Release/lib/static")
# message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# # Add main executable (the game, for example)
# add_executable(Shapes
#     src/main.cpp
#     src/Line2D.cpp
#     src/Shape2D.cpp
#     src/Triangle2D.cpp
#     src/Rectangle2D.cpp
#     src/Circle2D.cpp
# )

# # Find SDL2 package
# find_package(SDL2 REQUIRED)

# # Set the include directories for the main executable
# target_include_directories(Shapes PRIVATE 
#     ${CMAKE_SOURCE_DIR}/include
# )

# # Link SDL2 to the target
# target_link_libraries(Shapes PRIVATE ${SDL2_LIBRARIES})

# # Link to the Vec2D static library and header
# target_include_directories(Shapes PRIVATE ${VEC2D_INCLUDE_DIR})
# target_link_libraries(Shapes PRIVATE ${VEC2D_LIB_DIR}/libVec2D.a)


# # Lib Creation =============================================================== #

# # Set the base output directory for different build configurations
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/shared")
# # Set runtime output for executables (if you add any)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# # List source files
# set(SOURCES
#     src/Line2D.cpp
#     src/Shape2D.cpp
#     src/Triangle2D.cpp
#     src/Rectangle2D.cpp
#     src/Circle2D.cpp
# )

# # Create the static library
# add_library(ShapesStatic STATIC ${SOURCES})
# set_target_properties(ShapesStatic PROPERTIES
#     OUTPUT_NAME "Shapes"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
# )

# # Create the shared library
# add_library(ShapesShared SHARED ${SOURCES})
# set_target_properties(ShapesShared PROPERTIES
#     OUTPUT_NAME "Shapes"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
# )

# # Position Independent Code (PIC) is required for shared libraries
# target_compile_options(ShapesShared PRIVATE -fPIC)


# Minimum CMake version
cmake_minimum_required(VERSION 3.22)

# Project name and version
project(Shapes VERSION 1.0)

# C++ Version
set(CMAKE_CXX_STANDARD 20)

# Set the include directory for header files
include_directories(include)

# Vec2D library: set build and include paths
set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/include")
set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/build/Release/lib/static")
message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# Add main executable (the game, for example)
add_executable(Shapes
    src/main.cpp
    src/Line2D.cpp
    src/Shape2D.cpp
    src/Triangle2D.cpp
    src/Rectangle2D.cpp
    src/Circle2D.cpp
)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Set the include directories for the main executable
target_include_directories(Shapes PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${VEC2D_INCLUDE_DIR}
)

# Link SDL2 to the target
target_link_libraries(Shapes PRIVATE ${SDL2_LIBRARIES})

# Link to the Vec2D static library and header
target_link_libraries(Shapes PRIVATE ${VEC2D_LIB_DIR}/libVec2D.a)

# Lib Creation =============================================================== #

# Set the base output directory for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/shared")
# Set runtime output for executables (if you add any)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# List source files
set(SOURCES
    src/Line2D.cpp
    src/Shape2D.cpp
    src/Triangle2D.cpp
    src/Rectangle2D.cpp
    src/Circle2D.cpp
)

# Create the static library
add_library(ShapesStatic STATIC ${SOURCES})
set_target_properties(ShapesStatic PROPERTIES
    OUTPUT_NAME "Shapes"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
)
target_include_directories(ShapesStatic PRIVATE ${VEC2D_INCLUDE_DIR})
target_link_libraries(ShapesStatic PRIVATE ${VEC2D_LIB_DIR}/libVec2D.a)

# Create the shared library
add_library(ShapesShared SHARED ${SOURCES})
set_target_properties(ShapesShared PROPERTIES
    OUTPUT_NAME "Shapes"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
)
target_include_directories(ShapesShared PRIVATE ${VEC2D_INCLUDE_DIR})
target_link_libraries(ShapesShared PRIVATE ${VEC2D_LIB_DIR}/libVec2D.a)

# Position Independent Code (PIC) is required for shared libraries
target_compile_options(ShapesShared PRIVATE -fPIC)

