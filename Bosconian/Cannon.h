#ifndef CANNON
#define CANNON

#include "GameObject.h"

using namespace TextureAtlas::Station;

class Cannon : public GameObject {

public:

	Cannon(const Vec2& position) : GameObject(position, IN_GAME_RASTER_SIZE, NODE) {}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP || o->getClassId() == CLASS_ID_SHIP_PROJECTILE;
	}

	int getClassId() const override {
		return CLASS_ID_CANNON;
	}

};

#endif CANNON