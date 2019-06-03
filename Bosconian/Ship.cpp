#include "Ship.h"

void Ship::update(const float dt) {
	GameObject::update(dt);
}

void Ship::move(int direction) {
	changeMovement(Direction::mapping.at(direction));
	sprite = spriteMap.at(direction);
}
