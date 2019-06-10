#ifndef CHAR
#define CHAR

#include "Definitions.h"

class Char {

	const Vec2 position;
	const Vec2 size;
	const Mat4 transformation;

	const Rendering::Rectangle textureTransformation;

public:

	Char(char c, int x, int y, int w, int h) :
		position(Vec2(x, y)), size(Vec2(w, h)),
		transformation(Mat4::getTransformation(position, size)),
		textureTransformation(TextureAtlas::Font::numberMap.at(c)) {}

	Vec2 getPosition() const { return position; }
	Vec2 getSize() const { return size; }

	Rendering::RenderUnit getTextureTransformation() const {
		return { transformation, textureTransformation };
	}

};

#endif CHAR