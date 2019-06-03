#ifndef FORMATION
#define FORMATION

#include "Member.h"

class Formation {

	const GameObject* const leader;
	const vector<Member*> members;

public:

	Formation(const GameObject* const leader, const vector<Member*> members) : leader(leader), members(members) {}

	void update(float dt) {
		const Vec2& leaderDirection = leader->getDirection();
		const Vec2& leaderMovement = leader->getMovement();
		const Rendering::Rectangle& leaderSprite = leader->sprite;

		for (Member* const m : members) {
			if (m->destroyed)
				continue;

			if (leader->destroyed) {
				m->flyAway();
			} else {
				m->setDirection(leaderDirection);
				m->setMovement(leaderMovement);
				m->sprite = leaderSprite;
			}
		}
	}


};

#endif FORMATION
