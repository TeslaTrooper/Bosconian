#ifndef MEMBER
#define MEMBER

#include <structs.h>
#include "Enemy.h"

class Member : public Enemy {

	bool isFlyingAway;

public:
	Member(const Vec2& position, int enemyType, const GameObject* const player) :
		Enemy(position, enemyType, player), isFlyingAway(false) {
		setVMax(ENEMY_SPEED);
		setAcceleration(ENEMY_SPEED);
	}

	void update(float dt) override {
		GameObject::update(dt);
	}

	void flyAway() {
		if (isFlyingAway)
			return;

		// TODO It would be nice, if member changes direction
		// when leader gets destroyed (low prio)
	}

	int getClassId() const override {
		return CLASS_ID_ENEMY_TYPE_1;
	}

};

#endif MEMBER