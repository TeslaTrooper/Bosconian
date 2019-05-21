#version 330 core

in vec3 textureCoords;
out vec4 color;

uniform sampler2D tex;

uniform mat4 view;

void main() {
	// We use the view matrix to perform a
	// translation of texture coords in order
	// to produce the illusion of moving stars
	mat4 viewTransformation = view;

	// The stars should move slower, than other
	// object in the foreground.
	// This can be achieved by decreasing the
	// translation value. (In this case, it is 50%)
	// We also have to flip the values (minus sign)
	// in order to compensate the flipped values in
	// the camera matrix class
	viewTransformation[3][0] /= -2.f;
	viewTransformation[3][1] /= -2.f;

	vec2 coord = (viewTransformation * vec4(textureCoords, 1.f)).xy;

	ivec2 textureSize2d = textureSize(tex,0);
	float resX = float(textureSize2d.x);
	float resY = float(textureSize2d.y);

	vec2 res = vec2(resX, resY);

	// normalize texture coordinates from pixel
	// to relative values
	coord /= res;

	color = texture(tex, coord);
}