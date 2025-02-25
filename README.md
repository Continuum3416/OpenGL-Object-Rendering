# Graphics Programming with OpenGL

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)

[comment]: <> (Source: https://ileriayo.github.io/markdown-badges/)

## Overview


> "All these codes, just to render a cube? - Yes"


This is a CMake project setup for common OpenGL libraries, which includes GLFW, GLAD, GLEW, GLM, and FreeGLUT. The project also rendered some common computer Graphics Objects such as triangles, sphere, cubes, or tori (plural of torus). The CMake I wrote is mostly for MSVC. If you'd like to use other compilers, please modify the CMake.

Minimum Requirements: 
1. C++17
2. C17
3. [CMake](https://cmake.org/) 3.10

## Libraries for OpenGL applications

*Reference: https://github.com/eug/awesome-opengl*

* [assimp](https://github.com/assimp/assimp) - Portable library to import 3D models in a uniform manner.
* [Bullet](http://bulletphysics.org/wordpress) - It provides state of the art collision detection, soft body and rigid body dynamics.
* [fltk](https://www.fltk.org/) - C++ Toolkit to generate UI widgets portably. [LGPLv2](https://www.fltk.org/COPYING.php)
* [freeGLUT](http://freeglut.sourceforge.net) - Mature library that allows to create/manage windows containing OpenGL contexts.
* [GLFW](http://www.glfw.org) - Modern library for creating/interact windows with OpenGL contexts.
* [GLFM](https://github.com/brackeen/glfm) - Supplies an OpenGL ES context and input events for mobile devices and the web.
* [glm](http://glm.g-truc.net/0.9.6/index.html) - Mathematics library for graphics software based on the GLSL specifications.
* [Magnum](https://github.com/mosra/magnum) - It is a 2D/3D graphics engine for modern OpenGL.
* [MathFu](http://google.github.io/mathfu/) - C++ math library developed primarily for games focused on simplicity and efficiency.
* [Newton](http://newtondynamics.com/forum/newton.php) - It is a cross-platform life-like physics.
* [OGLplus](http://oglplus.org) - Collection of libraries which implement an object-oriented facade over OpenGL.
* [SDL](http://www.libsdl.org) - Designed to provide low level access to multimedia and graphics hardware.
* [SFML](http://www.sfml-dev.org) - Simple interface to ease the development of games and multimedia applications.
* [SOIL](http://www.lonesock.net/soil.html) - Tiny C library used primarily for uploading textures into OpenGL. (see [SOIL2](https://bitbucket.org/SpartanJ/soil2))
* [Pangolin](https://github.com/stevenlovegrove/Pangolin) - Lightweight portable rapid development library for managing OpenGL display / interaction and abstracting video input.
* [morphologica](https://github.com/ABRG-Models/morphologica) - OpenGL graphics engine for data visualization, especially of numerical simulations.
* [raylib](https://github.com/raysan5/raylib) - A simple and easy-to-use library to enjoy videogames programming.

## Installations

* [GLFW](https://www.glfw.org/download). There are two options: build from source using CMake or use prebuilt binaries.
* [GLAD](https://glad.dav1d.de/). Select API > gl > Latest Version. The API version doesn't matter, as long as it is greater than the GLFW version you're using. After that, go to Profile > Core, then press "Generate" and download the zip folder.
* [GLEW](https://glew.sourceforge.net/index.html). You can download the .zip folder directly and use it.
* [GLM](https://github.com/g-truc/glm/tags). This is a header-only library, so linking is very straightforward.
* FreeGLUT. There are two options, you can either install from [source](https://sourceforge.net/projects/freeglut/), or use [FreeGLUT MSVC](https://www.transmissionzero.co.uk/software/freeglut-devel/) specification as I did.

## Build

Create a `build` directory

```bash
mkdir build
cd build
```

**Configure**, **build**, and **run** the project with **release** (recommended)

```bash
cmake --build ./build/ --config Release
./build/Release/{file-name}
```

or with **debug**:

```bash
cmake --build ./build/ --config Debug
./build/Debug/{file-name}
```

Same thing for window, but remember to change to backward slash `\` and run with .exe instead.

## Demo

Rotating Cube Rendering:

<p align="center">
<img alt="70k-objects" src="images/rotating-cube.png" width="550">
</p>

Rotating Hollow Sphere Rendering:

<p align="center">
<img alt="70k-objects" src="images/rotating-sphere.png" width="550">
</p>

Rotating Donut Rendering:

<p align="center">
<img alt="70k-objects" src="images/rotating-donut.png" width="550">
</p>

## Note:

I will add more libraries and write better cmake scripts in the future.

