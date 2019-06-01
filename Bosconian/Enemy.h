#ifndef ENEMY
#define ENEMY

#include "GameObject.h"

class Enemy : public GameObject {


public:

	Enemy(const Vec2& position, const Rendering::Rectangle& sprite) :
		GameObject(position, IN_GAME_RASTER_SIZE, sprite) {}

	bool canCollideWith(const Entity* const e) const override {
		int id = ((GameObject*) e)->getClassId();

		// Can collide with ship / projetile / obstacles
		return id != CLASS_ID_CANNON && id != CLASS_ID_STATION_CONNECTOR &&
			id != CLASS_ID_STATION_CORE && id != CLASS_ID_STATION_PROJECTILE && id != CLASS_ID_ENEMY;
	}

	int getClassId() const override {
		return CLASS_ID_ENEMY;
	}

};

#endif ENEMY