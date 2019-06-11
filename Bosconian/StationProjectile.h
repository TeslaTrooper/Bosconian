#ifndef STATION_PROJECTILE
#define STATION_PROJECTILE

#include "GameObject.h"

using namespace TextureAtlas::Station;

class StationProjectile : public GameObject {

public:

	StationProjectile(const Vec2& position, const Vec2& size, const Rendering::Rectangle sprite) : GameObject(position, size, sprite) {}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP;
	}

	int getClassId() const override {
		return CLASS_ID_STATION_PROJECTILE;
	}

	void checkLifetime() override {
		if (lifetime > STATION_BULLET_LIFETIME)
			canBeCleanedUp = true;
	}

};

#endif STATION_PROJECTILE