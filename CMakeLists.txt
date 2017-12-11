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

# Collect files
file (GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

# Define executable target
add_executable(cg1-beleg ${SOURCE_FILES})
target_link_libraries(cg1-beleg ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})
