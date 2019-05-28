#pragma once

#include <Vec2.h>
#include "Definitions.h"

#define RANGE 200
#define PROJECTILE_INTERVAL 2
#define ROCKET_INTERVAL 5
#define PROJECTILE_SPEED 150

using namespace Station;

class StationAI {

	bool isActive;
	float lifetime, lastShootingTimeStamp;

	const Vec2 position;
	vector<Vec2> cannonPositions;

	ProjectileParams* projectileParams;

	struct MinElement {
		const int index;
		const float value;

		MinElement(int index, float value) : index(index), value(value) {}
	};

	vector<float> calcDistances(const Vec2& playerPosition) const {
		vector<float> result;

		for (int i = 0; i < cannonPositions.size(); i++)
			result.push_back(((cannonPositions.at(i) - playerPosition)).length());

		return result;
	}

	MinElement getMinDistance(const vector<float>& distances) const {
		vector<float>::const_iterator iter = min_element(distances.begin(), distances.end());
		int index = (int) distance(distances.begin(), iter);

		return { index, *iter };
	}

public:

	StationAI(const Vec2& position) : position(position), isActive(true), lifetime(0.f), lastShootingTimeStamp(0.f) {
		cannonPositions.push_back(getLeftCannonPosition(position));
		cannonPositions.push_back(getLeftBottomCannonPosition(position));
		cannonPositions.push_back(getLeftTopCannonPosition(position));

		cannonPositions.push_back(getRightCannonPosition(position));
		cannonPositions.push_back(getRightBottomCannonPosition(position));
		cannonPositions.push_back(getRightTopCannonPosition(position));
	}

	void update(float dt, const Vec2& playerPosition) {
		lifetime += dt;
		projectileParams = nullptr;

		if (!isActive || (lifetime - lastShootingTimeStamp) <= PROJECTILE_INTERVAL)
			return;

		MinElement min = getMinDistance(calcDistances(playerPosition));
		if (min.value > RANGE)
			return;

		Vec2 cannonPosition = cannonPositions.at(min.index);
		Vec2 projectileDirection = (playerPosition - cannonPosition).norm(PROJECTILE_SPEED);

		projectileParams = new ProjectileParams(cannonPosition, projectileDirection);

		lastShootingTimeStamp = lifetime;
	}

	bool canShoot() const {
		return projectileParams != nullptr;
	}

	ProjectileParams* getProjectileParams() const {
		return projectileParams;
	}

};