cmake_minimum_required(VERSION 3.10)

# Project name
project(OpenGLProject C CXX)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

# Specify the C++ and C standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optimization Flags
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")  # MSVC Flag
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")  # GCC/Clang Flag
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
endif()

# Define paths
set(GLFW_DIR "C:/Libraries/OpenGL/glfw-3.4")
set(GLAD_DIR "C:/Libraries/OpenGL/glad")
set(GLM_DIR "C:/Libraries/OpenGL/glm-1.0.1")
set(GLEW_DIR "C:/Libraries/OpenGL/glew-2.2.0")
set(FREEGLUT_DIR "C:/Libraries/OpenGL/freeglut-msvc") 

# Add the Glad source files
set(GLAD_SRC_DIR "${GLAD_DIR}/src")
file(GLOB GLAD_SRC_FILES ${GLAD_SRC_DIR}/*.c)

# Include directories
include_directories(
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${GLM_DIR}
    ${GLEW_DIR}/include
    ${FREEGLUT_DIR}/include
)

# Add GLFW as a subdirectory to build from source
set(GLFW_BUILD_DIR "${CMAKE_BINARY_DIR}/glfw_build")
add_subdirectory(${GLFW_DIR} ${GLFW_BUILD_DIR})

set(GLEW_LIB_DIR "${GLEW_DIR}/lib/Release/x64/glew32s.lib")

# Add FreeGLUT library directory
set(FREEGLUT_LIB_DIR "${FREEGLUT_DIR}/lib/x64/freeglut.lib")
set(FREEGLUT_DLL_DIR "${FREEGLUT_DIR}/bin/x64/freeglut.dll")

file(GLOB C_SOURCES "src/*.c")
file(GLOB CPP_SOURCES "src/*.cpp")

# For each test file, create a target
foreach(SOURCE_FILE ${C_SOURCES} ${CPP_SOURCES})
    # Extract the base name (without extension) to use as the target name
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    
    # Create executable for each source file
    add_executable(${TARGET_NAME} ${SOURCE_FILE} ${GLAD_SRC_FILES})
    
    # Link SFML libraries to each executable
    target_link_libraries(${TARGET_NAME} glfw ${GLEW_LIB_DIR} ${FREEGLUT_LIB_DIR} opengl32 gdi32 user32)

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREEGLUT_DLL_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endforeach()
