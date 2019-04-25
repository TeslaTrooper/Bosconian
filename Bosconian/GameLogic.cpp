#include "GameLogic.h"

vector<RenderUnit> GameLogic::getRenderUnits() const {
	vector<RenderUnit> result;

	Mat4 transformation = objects.at(0)->getTransformation();
	Rectangle texture = { Vec2(1, 0), Vec2(1, 1) };

	result.push_back({ transformation, texture });

	return result;
}