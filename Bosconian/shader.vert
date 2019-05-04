#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture;

out vec3 textureCoords;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat3 textureTranslation;

void main() {
	gl_Position = projection * view * transform * vec4(position, 0.0f, 1.0f);
	textureCoords = textureTranslation * vec3(texture, 1.0f);
}