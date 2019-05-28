#ifndef STATION_PROJECTILE
#define STATION_PROJECTILE

#include "GameObject.h"

using namespace TextureAtlas::Station;

class StationProjectile : public GameObject {

public:

	StationProjectile(const Vec2& position) : GameObject(position, IN_GAME_RASTER_SIZE/2.f, NODE) {}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP;
	}

	int getClassId() const override {
		return CLASS_ID_STATION_PROJECTILE;
	}

};

#endif STATION_PROJECTILE