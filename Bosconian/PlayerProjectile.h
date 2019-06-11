#ifndef PLAYER_PROJECTILE
#define PLAYER_PROJECTILE

#include "GameObject.h"

class PlayerProjectile : public GameObject {

public:

	PlayerProjectile(const Vec2& position, float angle) : GameObject(position, IN_GAME_RASTER_SIZE * Vec2(.75f, .1f), angle, TextureAtlas::Missile::PLAYER_BULLET) {}

	bool canCollideWith(const Entity* const e) const override {
		GameObject* o = (GameObject*)e;

		return o->getClassId() != CLASS_ID_SHIP && o->getClassId() != CLASS_ID_SHIP_PROJECTILE;
	}

	int getClassId() const override {
		return CLASS_ID_SHIP_PROJECTILE;
	}

	void checkLifetime() override {
		if (lifetime > SHIP_BULLET_LIFETIME)
			canBeCleanedUp = true;
	}

	bool canAnimate() override { return false; }

	void destroy() override {
		canBeCleanedUp = true;
	}

};

#endif PLAYER_PROJECTILE