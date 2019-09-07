#version 330 core

layout (location = 0) in vec2 position;

out vec3 textureCoords;

uniform mat4 transform;
uniform mat4 projection;

void main() {
	gl_Position = projection * transform * vec4(position, 0.0f, 1.0f);
};