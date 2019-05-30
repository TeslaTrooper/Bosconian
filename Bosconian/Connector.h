#ifndef CONNECTOR
#define CONNECTOR

#include "GameObject.h"

#define CONNECTOR_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 3)

class Connector : public GameObject {

public:

	Connector(const Vec2& position) : GameObject(position, CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS) {}

	virtual bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP || o->getClassId() == CLASS_ID_SHIP_PROJECTILE;
	};

	void destroy() override {}

	void destroyPart() {
		GameObject::destroy();
	}

};

#endif CONNECTOR