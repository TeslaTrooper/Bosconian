#ifndef SHIP
#define SHIP

#include "GameObject.h"

using namespace TextureAtlas::Ship;

class Ship : public GameObject {

	float lastShootingTimeStamp;

	void changeMovement(const Vec2& direction) {
		setDirection(direction);
		setMovement(direction.norm(SHIP_SPEED));
	}

public:

	Ship(const Vec2 position) : GameObject(position, IN_GAME_RASTER_SIZE, SPRITE_UP), lastShootingTimeStamp(0) {};

	void update(const float dt) override;
	void move(int direction);

	bool canCollideWith(const Entity* const e) const override {
		int classId = ((GameObject*)e)->getClassId();

		return classId != CLASS_ID_SHIP && classId != CLASS_ID_SHIP_PROJECTILE;
	}

	bool canShoot() {
		if ((lifetime - lastShootingTimeStamp) > SHIP_SHOOTING_INTERVAL && !isDestroyed()) {
			lastShootingTimeStamp = lifetime;

			return true;
		}

		return false;
	}

	int getClassId() const override {
		return CLASS_ID_SHIP;
	}

};

#endif SHIP
