#version 330 core
in vec3 ourColor;  // Color passed from the vertex shader
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0f); // Set the color of the fragment
}