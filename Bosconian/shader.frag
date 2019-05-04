#version 330 core

in vec3 textureCoords;
out vec4 color;
uniform sampler2D tex;
uniform vec2 pivot;

void main() {
	vec2 coord = textureCoords.xy;
	float u_angle = 0;

	vec2 pivot_t = vec2(0.5, 0.5);

	float sin_factor = sin(u_angle);
    float cos_factor = cos(u_angle);

	ivec2 textureSize2d = textureSize(tex,0);
	float resX = float(textureSize2d.x);
	float resY = float(textureSize2d.y);

	vec2 res = vec2(resX, resY);

    coord = (coord - pivot) * mat2(cos_factor, sin_factor, -sin_factor, cos_factor);
    coord += pivot;

	// normalize texture coordinates from pixel
	// to relative values
	coord /= res;

	color = texture(tex, coord);
	//color = vec4(1,1,1,1);
}