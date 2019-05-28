#ifndef CANNON
#define CANNON

#include "GameObject.h"

using namespace TextureAtlas::Station;

class Cannon : public GameObject {

	bool damaged;

public:

	Cannon(const Vec2& position) : GameObject(position, IN_GAME_RASTER_SIZE, NODE), damaged(false) {}

	void update(const float dt) override {
		if (damaged)
			sprite = NODE_DAMAGED;
	}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP || o->getClassId() == CLASS_ID_SHIP_PROJECTILE;
	}

	int getClassId() const override {
		return CLASS_ID_CANNON;
	}

	bool isDamaged() { return damaged; };
	void damage() { damaged = true; };

};

#endif CANNON