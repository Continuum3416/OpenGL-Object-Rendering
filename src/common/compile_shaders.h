#ifndef COMPILE_SHADERS
#define COMPILE_SHADERS


#include <GLFW/glfw3.h>
#include <string>
#include "read_file.h"

unsigned int shaderProgram;

void compileShaders(const char* vertex, const char* fragment) 
{
    std::string vertexCode = readShaderFile(vertex);
    std::string fragmentCode = readShaderFile(fragment);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

#endif