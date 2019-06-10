#ifndef LABEL
#define LABEL

#include <string>
#include <vector>

#include "Char.h"

#define DEFAULT_CHAR_WIDTH	20
#define DEFAULT_CHAR_HEIGHT 20

using namespace std;

class Label {

	vector<Char> chars;

public:

	Label(string text, int x, int y) {
		for (int i = 0; i < text.size(); i++)
			chars.push_back(Char(text.at(i), x + (i * DEFAULT_CHAR_WIDTH), y, DEFAULT_CHAR_WIDTH, DEFAULT_CHAR_HEIGHT));
	}

	vector<Rendering::RenderUnit> getRenderUnits() const {
		vector<Rendering::RenderUnit> units;

		for (const Char& c : chars)
			units.push_back(c.getTextureTransformation());

		return units;
	}

};

#endif LABEL