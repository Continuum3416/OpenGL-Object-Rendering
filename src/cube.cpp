#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "common/init_opengl.h"
#include "common/read_file.h"
#include "common/compile_shaders.h"

// Vertices and colors for the cube
float vertices[] = {
    // Positions          // Colors (RGB)
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Front (red)
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Front (green)
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Front (blue)
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Front (yellow)

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  // Back (cyan)
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  // Back (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Back (white)
    -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  // Back (gray)

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom (red)
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Bottom (green)
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Bottom (blue)
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Bottom (yellow)

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Top (cyan)
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Top (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Top (white)
    -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  // Top (gray)

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Left (red)
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Left (green)
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Left (blue)
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Left (yellow)

     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Right (cyan)
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Right (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Right (white)
     0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f   // Right (gray)
};

// Indices for the cube's faces
unsigned int indices[] = {
    0, 1, 2,  0, 2, 3,  // Front
    4, 5, 6,  4, 6, 7,  // Back
    8, 9, 10, 8, 10, 11, // Bottom
    12, 13, 14, 12, 14, 15, // Top
    16, 17, 18, 16, 18, 19, // Left
    20, 21, 22, 20, 22, 23  // Right
};


// Shader program setup
unsigned int VAO, VBO, EBO;

void setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

GLFWwindow* window;
const int width = 1000, height = 1000;

int main() {
    initOpenGL(window, width, height);
    compileShaders("shaders/cube/vertex_shader.glsl", "shaders/cube/fragment_shader.glsl");
    setupBuffers();

    // Matrix and transformation setup
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 transform = projection * view * model;
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.1f, 0.3f, 0.5f));

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\cube.exe
// cmake --build .\build\ --config Release; .\build\Release\cube.exe