cmake_minimum_required(VERSION 3.10)

# Set up project
project(PortalSimulator VERSION 0.1)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

# Link libraries
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add executable
file(GLOB SOURCES src/*.cpp)
add_executable(PortalSimulator ${SOURCES} glad/glad.c)

# Configure output directory
set_target_properties(PortalSimulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY build/)

# Link required libraries
target_link_libraries(PortalSimulator glfw OpenGL::GL ${CMAKE_DL_LIBS})

# Configure include directores
target_include_directories(PortalSimulator
    PRIVATE include/
    PRIVATE glad/include/
    PRIVATE ${GLM_INCLUDE_DIR}
)
