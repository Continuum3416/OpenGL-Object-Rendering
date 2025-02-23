# OpenGL Project Setup

Overview: this is a CMake project setup for common OpenGL libraries, which includes GLFW, GLAD, GLEW, GLM, and FreeGLUT. I will add more in the future.

Minimum Requirements: 
1. C++17
2. C11
3. [CMake](https://cmake.org/) 3.10

## Installations

Libraries:
1. [GLFW](https://www.glfw.org/download). There are two options: build from source using CMake or use prebuilt binaries.
2. [GLAD](https://glad.dav1d.de/). Select API > gl > Latest Version. The API version doesn't matter, as long as it is greater than the GLFW version you're using. After that, go to Profile > Core, then press "Generate" and download the zip folder.
3. [GLEW](https://glew.sourceforge.net/index.html). You can download the .zip folder directly and use it.
4. [GLM](https://github.com/g-truc/glm/tags). This is a header-only library, so linking is very straightforward.
5. FreeGLUT. There are two options, you can either install from [source](https://sourceforge.net/projects/freeglut/), or use [FreeGLUT MSVC](https://www.transmissionzero.co.uk/software/freeglut-devel/) specification as I did.