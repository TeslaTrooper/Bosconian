#ifndef STATION_PROJECTILE
#define STATION_PROJECTILE

#include "GameObject.h"

#define MAX_LIFETIME 3

using namespace TextureAtlas::Station;

class StationProjectile : public GameObject {

public:

	StationProjectile(const Vec2& position, const Rendering::Rectangle sprite) : GameObject(position, IN_GAME_RASTER_SIZE, sprite) {}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP;
	}

	int getClassId() const override {
		return CLASS_ID_STATION_PROJECTILE;
	}

	void checkLifetime() override {
		if (lifetime > MAX_LIFETIME)
			canBeCleanedUp = true;
	}

};

#endif STATION_PROJECTILE