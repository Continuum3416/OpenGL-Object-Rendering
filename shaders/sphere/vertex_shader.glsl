#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 transform;

out vec3 FragColor;

void main() {
    gl_Position = transform * vec4(aPos, 1.0);
    FragColor = aNormal * 0.5 + 0.5;
}
