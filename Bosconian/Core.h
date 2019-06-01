#ifndef CORE_CLASS
#define CORE_CLASS

#include "GameObject.h"

#define CORE_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 1)

class Core : public GameObject {

public:

	Core(const Vec2& position) : GameObject(position, CORE_SIZE, TextureAtlas::Station::CORE) {}

	virtual bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*)e;

		return o->getClassId() == CLASS_ID_SHIP || o->getClassId() == CLASS_ID_SHIP_PROJECTILE;
	};

	int getClassId() const override {
		return CLASS_ID_STATION_CORE;
	}


};

#endif CORE_CLASS