#version 330 core
out vec4 color;

in vec3 textureCoords;

uniform sampler2D tex;

void main() {
	ivec2 textureSize2d = textureSize(tex,0);
	float resX = float(textureSize2d.x);
	float resY = float(textureSize2d.y);

	vec2 res = vec2(resX, resY);
	vec2 coords = textureCoords.xy / res;

	color = texture(tex, coords);
	//color = vec4(1,1,1,1);
}