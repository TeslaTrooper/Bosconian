#ifndef CANNON
#define CANNON

#include "GameObject.h"

using namespace TextureAtlas::Station;

class Cannon : public GameObject {

	bool damaged;
	bool cleanupAfterAnimation;

public:

	Cannon(const Vec2& position) : GameObject(position, IN_GAME_RASTER_SIZE, NODE), damaged(false), cleanupAfterAnimation(false) {}

	void update(const float dt) override {
		GameObject::update(dt);

		if (damaged)
			sprite = NODE_DAMAGED;
	}

	void afterDestruction() override {
		if (cleanupAfterAnimation) {
			markForCleanup();
		} else {
			damaged = true;
			setBbox(getBbox() / 2);
			setPosition(getPosition() + getBbox() / 2);
			updateTransformation();
		}
	}

	void destroyPart() {
		if (damaged)
			markForCleanup();

		cleanupAfterAnimation = true;
		destroy();
	}

	bool canAnimate() override {
		return !damaged;
	}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*) e;

		return o->getClassId() == CLASS_ID_SHIP || o->getClassId() == CLASS_ID_SHIP_PROJECTILE;
	}

	int getClassId() const override {
		return CLASS_ID_CANNON;
	}

};

#endif CANNON