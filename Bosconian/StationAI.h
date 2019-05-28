#pragma once

#include <Vec2.h>

#include "Definitions.h"
#include "Cannon.h"

#define RANGE 200
#define PROJECTILE_INTERVAL 2
#define ROCKET_INTERVAL 5
#define PROJECTILE_SPEED 150

using namespace Station;

class StationAI {

	bool isActive;
	float lifetime, lastShootingTimeStamp;

	vector<Cannon*> cannons;

	ProjectileParams* projectileParams;

	struct MinElement {
		const int index;
		const float value;

		MinElement(int index, float value) : index(index), value(value) {}
	};

	vector<float> calcDistances(const Vec2& playerPosition) const {
		vector<float> result;

		for (int i = 0; i < cannons.size(); i++)
			result.push_back(((cannons.at(i)->getPosition() - playerPosition)).length());

		return result;
	}

	MinElement getMinDistance(const vector<float>& distances) const {
		vector<float>::const_iterator iter = min_element(distances.begin(), distances.end());
		int index = (int) distance(distances.begin(), iter);

		return { index, *iter };
	}

public:

	StationAI(const vector<Cannon*>& cannons) : isActive(true), lifetime(0.f), lastShootingTimeStamp(0.f) {
		for (Cannon* obj : cannons)
			this->cannons.push_back(obj);
	}

	void update(float dt, const Vec2& playerPosition) {
		lifetime += dt;
		projectileParams = nullptr;

		if (!isActive || (lifetime - lastShootingTimeStamp) <= PROJECTILE_INTERVAL)
			return;

		MinElement min = getMinDistance(calcDistances(playerPosition));
		if (cannons.at(min.index)->isDamaged() || min.value > RANGE)
			return;

		Vec2 cannonPosition = cannons.at(min.index)->getPosition();
		Vec2 projectileDirection = (playerPosition - cannonPosition).norm(PROJECTILE_SPEED);

		projectileParams = new ProjectileParams(cannonPosition, projectileDirection);

		lastShootingTimeStamp = lifetime;

		isActive = false;
		for (Cannon* c : cannons) {
			if (!c->isDamaged()) {
				isActive = true;
				break;
			}
		}
	}

	bool canShoot() const {
		return projectileParams != nullptr;
	}

	ProjectileParams* getProjectileParams() const {
		return projectileParams;
	}

};