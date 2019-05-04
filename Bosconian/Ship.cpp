#include "Ship.h"

void Ship::update(const float dt) {
	GameObject::update(dt);
}

void Ship::move(int direction) {
	if (direction == DIRECTION_LEFT) {
		changeMovement(Vec2(-1, 0));
		sprite = SPRITE_LEFT;
	}

	if (direction == DIRECTION_RIGHT){
		changeMovement(Vec2(1, 0));
		sprite = SPRITE_RIGHT;
	}

	if (direction == DIRECTION_DOWN){
		changeMovement(Vec2(0, -1));
		sprite = SPRITE_DOWN;
	}
	
	if (direction == DIRECTION_UP){
		changeMovement(Vec2(0, 1));
		sprite = SPRITE_UP;
	}
}
