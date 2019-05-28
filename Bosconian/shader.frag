#version 330 core

in vec3 textureCoords;
out vec4 color;

uniform sampler2D tex;

void main() {
	vec2 coord = textureCoords.xy;

	ivec2 textureSize2d = textureSize(tex,0);
	float resX = float(textureSize2d.x);
	float resY = float(textureSize2d.y);

	vec2 res = vec2(resX, resY);

	// normalize texture coordinates from pixel
	// to relative values
	coord /= res;

	color = texture(tex, coord);
	//color = vec4(1,1,1,1);
}