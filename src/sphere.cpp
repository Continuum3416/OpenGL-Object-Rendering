#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#define M_PI 3.14159f

#include "common/init_opengl.h"
#include "common/read_file.h"
#include "common/compile_shaders.h"

std::vector<float> vertices;
std::vector<unsigned int> indices;


// Sphere generation function
void generateSphere(float radius, int sector_count, int stack_count,
                    std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    float x, y, z, xy;
    float nx, ny, nz;
    float lengthInv = 1.0f / radius;
    float sectorStep = 2 * M_PI / sector_count;
    float stackStep = M_PI / stack_count;
    float sectorAngle, stackAngle;

    for (int i{0}; i <= stack_count; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j{0}; j <= sector_count; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }

    for (int i{0}; i < stack_count; ++i) {
        int k1 = i * (sector_count + 1);
        int k2 = k1 + sector_count + 1;

        for (int j{0}; j < sector_count; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stack_count - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// Window settings
GLFWwindow* window;
const int width = 1000, height = 1000;

// Main function
int main() {
    initOpenGL(window, width, height);
    compileShaders("shaders/sphere/vertex_shader.glsl", "shaders/sphere/fragment_shader.glsl");
    generateSphere(1.0f, 36, 18, vertices, indices);
    setupBuffers();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        glUseProgram(shader_program);
    
        glm::mat4 transform = projection * view * model;
        unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    
        // Enable wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    
        // Reset to fill mode if needed
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
        model = glm::rotate(model, glm::radians(0.01f), glm::vec3(0.1f, 1.0f, 0.0f));
    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\sphere.exe
// cmake --build .\build\ --config Release; .\build\Release\sphere.exe
