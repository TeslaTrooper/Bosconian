#pragma once

#include <Vec2.h>
#include "Definitions.h"

using namespace Station;

class StationAI {

	const Vec2 position;

public:

	StationAI(const Vec2& position) : position(position) {}

	void update(float dt, const Vec2& playerPosition) {

	}
};