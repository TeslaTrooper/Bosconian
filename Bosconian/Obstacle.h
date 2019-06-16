#ifndef OBSTACLE
#define OBSTACLE

#include "GameObject.h"

#define OBSTACLE_SIZE Vec2(40, 40)

class Obstacle : public GameObject {

	const int classId;

public:
	Obstacle(const Vec2& position, const Rendering::Rectangle sprite) : GameObject(position, OBSTACLE_SIZE, sprite),
		classId(sprite == TextureAtlas::Obstacle::ASTEROID ? CLASS_ID_ASTEROID : CLASS_ID_MINE) {}

	bool canCollideWith(const Entity* const e) const override {
		int id = ((GameObject*)e)->getClassId();

		// Can collide with ship / projetile / obstacles
		return id != CLASS_ID_CANNON && id != CLASS_ID_STATION_CONNECTOR &&
			id != CLASS_ID_STATION_CORE && id != CLASS_ID_STATION_PROJECTILE;
	}

	int getClassId() const override {
		return classId;
	}
};

#endif OBSTACLE