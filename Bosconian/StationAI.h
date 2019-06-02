#pragma once

#include <Vec2.h>

#include "Cannon.h"
#include "Connector.h"

#define RANGE 200
#define PROJECTILE_INTERVAL 2
#define ROCKET_INTERVAL 5
#define PROJECTILE_SPEED 150
#define ROCKET_SPEED 250

using namespace Station;

class StationAI {

	bool isActive;
	float lifetime, lastShootingTimeStamp, lastRocketShootingTimeStamp;

	GameObject* core;
	Connector* connectorLeft;
	Connector* connectorRight;

	vector<Cannon*> cannons;

	ProjectileParams* projectileParams;
	ProjectileParams* rocketParams;

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

	void doCannonLogic(const Vec2& playerPosition) {
		MinElement min = getMinDistance(calcDistances(playerPosition));
		if (cannons.at(min.index)->isDestroyed() || min.value > RANGE)
			return;

		Vec2 cannonPosition = cannons.at(min.index)->getPosition() + (cannons.at(min.index)->getBbox() / 2);
		Vec2 projectileDirection = (playerPosition - cannonPosition).norm(PROJECTILE_SPEED);

		projectileParams = new ProjectileParams(cannonPosition - (IN_GAME_RASTER_SIZE / 4), projectileDirection);

		lastShootingTimeStamp = lifetime;
	}

	bool isPlayerInArea(const Vec2& playerPosition) const {
		const Vec2& corePosition = core->getPosition();
		const Vec2& coreBbox = core->getBbox();

		return playerPosition.x >= corePosition.x && playerPosition.x <= corePosition.x + coreBbox.x;
	}

	void doRocketLogic(const Vec2& playerPosition) {
		if (!isPlayerInArea(playerPosition))
			return;

		Vec2 coreCenter = core->getPosition() + (core->getBbox() / 2);
		float distance = (coreCenter - playerPosition).length();

		if (distance > RANGE)
			return;

		if (playerPosition.y < coreCenter.y)
			rocketParams = new ProjectileParams(coreCenter, Vec2(0, -1).mul(ROCKET_SPEED));
		else
			rocketParams = new ProjectileParams(coreCenter, Vec2(0, 1).mul(ROCKET_SPEED));

		lastRocketShootingTimeStamp = lifetime;
	}

public:

	StationAI(const vector<GameObject*>& childObjects) : core(childObjects.at(2)), isActive(true), lifetime(0.f), lastShootingTimeStamp(0.f) {
		connectorLeft = (Connector*) childObjects.at(0);
		connectorRight = (Connector*) childObjects.at(1);

		for (int i = 3; i < 9; i++)
			this->cannons.push_back((Cannon*) childObjects.at(i));
	}

	void update(float dt, const GameObject* const player) {
		lifetime += dt;
		projectileParams = nullptr;
		rocketParams = nullptr;

		if (!isActive || player == nullptr)
			return;

		const Vec2& playerPosition = player->getPosition() + (player->getBbox() / 2);

		if ((lifetime - lastShootingTimeStamp) > PROJECTILE_INTERVAL)
			doCannonLogic(playerPosition);

		if ((lifetime - lastRocketShootingTimeStamp) > PROJECTILE_INTERVAL)
			doRocketLogic(playerPosition);

		isActive = false;
		for (GameObject* c : cannons) {
			if (!c->isDestroyed()) {
				isActive = true;
				break;
			}
		}

		if (!isActive || core->isDestroyed()) {
			connectorLeft->destroyPart();
			connectorRight->destroyPart();
			core->destroy();

			for (Cannon* c : cannons) {
				c->destroyPart();
			}
		}
	}

	bool canShootProjectile() const {
		return projectileParams != nullptr;
	}

	bool canShootRocket() const {
		return rocketParams != nullptr;
	}

	ProjectileParams* getProjectileParams() const {
		return projectileParams;
	}

	ProjectileParams* getRocketParams() const {
		return rocketParams;
	}

	bool inactive() {
		return !isActive;
	}

};