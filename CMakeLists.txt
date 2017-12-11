# Configure CMake
cmake_minimum_required(VERSION 3.3)
set (CMAKE_CXX_STANDARD 11)
project(cg1-beleg)

# Find dependencies
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Setup include directories
include_directories(${GLUT_INCLUDES} ${OPENGL_INCLUDES} ${GLEW_INCLUDES})

# Set up output file paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Collect files
file (GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

# Define executable target
add_executable(cg1-beleg ${SOURCE_FILES})
target_link_libraries(cg1-beleg ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})
