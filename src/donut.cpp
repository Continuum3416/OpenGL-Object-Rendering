#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#define M_PI 3.14157f

#include "common/init_opengl.h"
#include "common/read_file.h"
#include "common/compile_shaders.h"

const int numMajor = 50;  // Number of segments around the ring
const int numMinor = 20;  // Number of segments in the tube
const float majorRadius = 0.5f;  
const float minorRadius = 0.2f;

std::vector<float> vertices;
std::vector<unsigned int> indices;

void generateTorus() {
    for (int i{0}; i <= numMajor; ++i) {
        float u = i * 2.0f * M_PI / numMajor;
        float cosU = cos(u);
        float sinU = sin(u);

        for (int j{0}; j <= numMinor; ++j) {
            float v = j * 2.0f * M_PI / numMinor;
            float cosV = cos(v);
            float sinV = sin(v);

            // Torus vertex positions
            float x = (majorRadius + minorRadius * cosV) * cosU;
            float y = (majorRadius + minorRadius * cosV) * sinU;
            float z = minorRadius * sinV;

            // Color based on position
            float r = 0.5f + 0.5f * cosU;
            float g = 0.5f + 0.5f * sinV;
            float b = 0.5f + 0.5f * cosV;

            vertices.insert(vertices.end(), {x, y, z, r, g, b});
        }
    }

    // Create indices for rendering
    for (int i{0}; i < numMajor; ++i) {
        for (int j{0}; j < numMinor; ++j) {
            unsigned int curr = i * (numMinor + 1) + j;
            unsigned int next = (i + 1) * (numMinor + 1) + j;
            unsigned int nextRow = curr + 1;
            unsigned int diag = next + 1;

            indices.insert(indices.end(), {curr, next, nextRow});
            indices.insert(indices.end(), {next, diag, nextRow});
        }
    }
}

unsigned int VAO, VBO, EBO;

void setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
    compileShaders("shaders/donut/vertex_shader.glsl", "shaders/donut/fragment_shader.glsl");

    generateTorus();
    setupBuffers();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);

        glm::mat4 transform = projection * view * model;
        unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        model = glm::rotate(model, glm::radians(0.01f), glm::vec3(0.1f, 0.3f, 0.5f));

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\donut.exe
// cmake --build .\build\ --config Release; .\build\Release\donut.exe