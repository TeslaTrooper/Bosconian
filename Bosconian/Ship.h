#ifndef SHIP
#define SHIP

#include "GameObject.h"

#define SHIP_SPEED 100

using namespace TextureAtlas::Ship;

class Ship : public GameObject {

	void changeMovement(const Vec2& direction) {
		setDirection(direction);
		setMovement(direction * SHIP_SPEED);
	}

public:

	Ship(const Vec2 position, const Vec2 scale) : GameObject(position, scale, SPRITE_UP) {};

	void update(const float dt) override;
	void move(int direction);

	int getClassId() const override {
		return CLASS_ID_SHIP;
	}

};

#endif SHIP
