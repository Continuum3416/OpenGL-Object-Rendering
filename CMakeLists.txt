cmake_minimum_required(VERSION 3.18)
project(OpenGLProject C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Add the vcpkg library directory
set(vcpkg_lib "C:/vcpkg/installed/x64-windows/lib")
link_directories(${vcpkg_lib})

# Ensure consistent runtime library
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    else()
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
        # additional optimization flags:
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native -DNDEBUG")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -DNDEBUG")
    endif()
endif()

# Find OpenGL and required libraries from vcpkg
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(FreeGLUT REQUIRED)
find_package(glad CONFIG REQUIRED) 

# Gather source files
file(GLOB C_SOURCES "src/*.c")
file(GLOB CPP_SOURCES "src/*.cpp")

foreach(SOURCE_FILE ${C_SOURCES} ${CPP_SOURCES})
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL 
        glfw GLEW::GLEW glm FreeGLUT::freeglut glad)
endforeach()
