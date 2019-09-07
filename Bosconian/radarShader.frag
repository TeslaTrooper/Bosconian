#version 330 core

out vec4 color;

uniform vec3 clr;

void main() {
    color = vec4(clr, 1.0f);
} 