# Minimum CMake version
cmake_minimum_required(VERSION 3.22)

# Project name and version
project(Graphics VERSION 1.0)

# C++ Version
set(CMAKE_CXX_STANDARD 20)

# Dependencies =============================================================== #
# Vec2D library (shared): set build and include paths
set(VEC2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/include")
set(VEC2D_LIB_DIR "${CMAKE_SOURCE_DIR}/../Vec2D/build/Release/lib/shared")  # or ".../lib/static"
message("VEC2D_LIB_DIR is set to: ${VEC2D_LIB_DIR}")

# Shapes library (shared): set build and include paths
set(SHAPES_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../Shapes/include")
set(SHAPES_LIB_DIR "${CMAKE_SOURCE_DIR}/../Shapes/build/Release/lib/shared") # or ".../lib/static"
message("SHAPES_LIB_DIR is set to: ${SHAPES_LIB_DIR}")

# Find SDL2 package
find_package(SDL2 REQUIRED)
# Dependencies - End ========================================================= #

# Set the include directory for header files
include_directories(include)

# Add main executable
add_executable(Graphics
    src/main.cpp
    src/Color.cpp
    src/graphics_utils.cpp
    src/Screen.cpp
    src/ScreenBuffer.cpp
)

# Set the include directories for the main executable
target_include_directories(Graphics PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${VEC2D_INCLUDE_DIR}  # Vec2D headers
    ${SHAPES_INCLUDE_DIR}  # Shapes headers
)

target_link_libraries(Graphics PRIVATE
    ${SDL2_LIBRARIES}  # SDL2
    ${VEC2D_LIB_DIR}/libVec2D.so  # or ".a"
    ${SHAPES_LIB_DIR}/libShapes.so  # or ".a"
)

# Library Creation =========================================================== #

# Set the base output directory for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/static")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/shared")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # runtime output for executables (if any)

# List source files
set(SOURCES
    src/Color.cpp
    src/graphics_utils.cpp
    src/Screen.cpp
    src/ScreenBuffer.cpp
)

# Create the static library
add_library(GraphicsStatic STATIC ${SOURCES})
set_target_properties(GraphicsStatic PROPERTIES
    OUTPUT_NAME "Graphics"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
)
# Include dependies into Graphics library (Static)
target_include_directories(GraphicsStatic PRIVATE 
    ${VEC2D_INCLUDE_DIR}  # Vec2D headers
    ${SHAPES_INCLUDE_DIR}  # Shapes headers
)
target_link_libraries(GraphicsStatic PRIVATE 
    ${VEC2D_LIB_DIR}/libVec2D.so  # Vec2D lib (Shared)
    ${SHAPES_LIB_DIR}/libSheps.so  # Shapes lib (Shared)
)

# # Create the shared library
# add_library(GraphicsShared SHARED ${SOURCES})
# set_target_properties(GraphicsShared PROPERTIES
#     OUTPUT_NAME "Graphics"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
# )
# # Include dependies into Graphics library (Shared)
# target_include_directories(GraphicsShared PRIVATE 
#     ${VEC2D_INCLUDE_DIR}  # Vec2D headers
#     ${SHAPES_INCLUDE_DIR}  # Shapes headers
# )
# target_link_libraries(GraphicsShared PRIVATE 
#     ${VEC2D_LIB_DIR}/libVec2D.so  # Vec2D lib (Shared)
#     ${SHAPES_LIB_DIR}/libSheps.so  # Shapes lib (Shared)
# )

# Position Independent Code (PIC) is required for shared libraries or static included in shared library
target_compile_options(GraphicsStatic PRIVATE -fPIC)
# target_compile_options(GraphicsShared PRIVATE -fPIC)


