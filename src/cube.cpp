#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;  // Position
    layout (location = 1) in vec3 aColor; // Color
    out vec3 ourColor;  // Output color to fragment shader
    uniform mat4 transform;

    void main() {
        gl_Position = transform * vec4(aPos, 1.0);
        ourColor = aColor; // Pass color to fragment shader
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 ourColor;  // Color passed from the vertex shader
    out vec4 FragColor;

    void main() {
        FragColor = vec4(ourColor, 1.0f); // Set the color of the fragment
    }
)";

// Vertices and colors for the cube
float vertices[] = {
    // Positions         // Colors (RGB)
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Front face (red)
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Front face (green)
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Front face (blue)
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Front face (yellow)

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  // Back face (cyan)
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  // Back face (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Back face (white)
    -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  // Back face (gray)

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom face (red)
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Bottom face (green)
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Bottom face (blue)
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Bottom face (yellow)

    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Top face (cyan)
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Top face (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Top face (white)
    -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  // Top face (gray)

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Left face (red)
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Left face (green)
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Left face (blue)
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Left face (yellow)

     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Right face (cyan)
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Right face (magenta)
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // Right face (white)
     0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f   // Right face (gray)
};

// Indices for the cube's faces
unsigned int indices[] = {
    0, 1, 2,  0, 2, 3,  // Front face
    4, 5, 6,  4, 6, 7,  // Back face
    8, 9, 10, 8, 10, 11, // Bottom face
    12, 13, 14, 12, 14, 15, // Top face
    16, 17, 18, 16, 18, 19, // Left face
    20, 21, 22, 20, 22, 23  // Right face
};

// GLFW window setup
GLFWwindow* window;
int width = 800, height = 600;

// Shader program setup
unsigned int vertexShader, fragmentShader, shaderProgram;
unsigned int VAO, VBO, EBO;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);  // Set the OpenGL viewport to match the new window size
}

void initOpenGL() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create windowed mode window and OpenGL context
    window = glfwCreateWindow(width, height, "Rotating Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void compileShaders() {
    // Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete shaders after linking them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void setupBuffers() {
    // Create and bind VAO, VBO, and EBO
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

int main() {
    initOpenGL();
    compileShaders();
    setupBuffers();

    // Matrix and transformation setup
    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        // Input handling
        glfwPollEvents();

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader program
        glUseProgram(shaderProgram);

        // Transformation matrix
        glm::mat4 transform = projection * view * model;
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Draw cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Rotate the model
        model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.1f, 0.3f, 0.5f));

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\cube.exe
// cmake --build .\build\ --config Release; .\build\Release\main.exe