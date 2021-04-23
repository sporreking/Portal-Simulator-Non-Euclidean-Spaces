cmake_minimum_required(VERSION 3.10)

# Set up project
project(PortalSimulator VERSION 0.1)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

# Add executable
file(GLOB SOURCES src/*.cpp)
file(GLOB LIBS lib/*.c)
add_executable(PortalSimulator ${SOURCES} glad/glad.c ${LIBS})

# Configure output directory
set_target_properties(PortalSimulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY build/)

if (WIN32)
    message("Compiling for Windows...")

    if (MINGW)
        message("MinGW found!")

        get_filename_component(MINGWBINPATH ${CMAKE_C_COMPILER} PATH)
        if (NOT EXISTS ${MINGWBINPATH}/../include)
            message(FATAL_ERROR "Could not find include directory: ${MINGWBINPATH}/../include")
        endif()

    else()
        message(FATAL_ERROR "Could not find MinGW!")
    endif()

    # Link libraries
    find_package(OpenGL REQUIRED)

    # Link required libraries
    target_link_libraries(PortalSimulator glfw3 OpenGL::GL ${CMAKE_DL_LIBS})

    # Configure include directores
    target_include_directories(PortalSimulator
        PRIVATE include/
        PRIVATE glad/include/
        PRIVATE ${MINGWBINPATH}/../include
    )

elseif(UNIX)
    message("Compiling for Unix...")

    # Link libraries
    find_package(glfw3 3.3 REQUIRED)
    find_package(OpenGL REQUIRED)

    # Link required libraries
    target_link_libraries(PortalSimulator glfw OpenGL::GL ${CMAKE_DL_LIBS})

    # Configure include directores
    target_include_directories(PortalSimulator
        PRIVATE include/
        PRIVATE glad/include/
        PRIVATE ${GLM_INCLUDE_DIR}
    )
endif()