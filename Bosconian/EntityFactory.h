#pragma once

#include <vector>
#include <Entity.h>

#include "Ship.h"
#include "StationAI.h"
#include "EntityHandler.h"
#include "Cannon.h"
#include "StationProjectile.h"
#include "Connector.h"
#include "Core.h"

#define OBSTACLE_SIZE Vec2(40, 40)

using namespace Station;

class EntityFactory {

	EntityHandler* const entityHandler;

	void configureProjectile(const ProjectileParams* const params, GameObject* const object) const {
		object->setVMax(params->direction.length());
		object->setAcceleration(params->direction.length());
		object->setDirection(params->direction.norm());
		object->setMovement(params->direction);

		entityHandler->registerEntity(object);
	}

public:

	EntityFactory(EntityHandler* const entityHandler) :
		entityHandler(entityHandler) {}

	
	Ship* createShip(const Vec2& position) const {
		Ship* ship = new Ship(position);

		ship->setVMax(100);
		ship->setAcceleration(100);
		ship->setDirection(Vec2(0, 1));

		return (Ship*) entityHandler->registerEntity(ship);
	}

	GameObject* createAsteroid(const Vec2& position) const {
		GameObject* asteroid = new GameObject(position, OBSTACLE_SIZE, TextureAtlas::Obstacle::ASTEROID);

		asteroid->setVMax(0);
		asteroid->setAcceleration(0);

		return entityHandler->registerEntity(asteroid);
	}

	GameObject* createMine(const Vec2& position) const {
		GameObject* mine = new GameObject(position, OBSTACLE_SIZE, TextureAtlas::Obstacle::MINE);

		mine->setVMax(0);
		mine->setAcceleration(0);

		return entityHandler->registerEntity(mine);
	}

	StationAI* createStation(const Vec2& position) const {
		vector<GameObject*> childObjects;

		childObjects.push_back(new Connector(position));
		childObjects.push_back(new Connector(getRightConnectorPosition(position)));
		childObjects.push_back(new Core(getCorePosition(position)));
		childObjects.push_back(new Cannon(getLeftCannonPosition(position)));
		childObjects.push_back(new Cannon(getLeftBottomCannonPosition(position)));
		childObjects.push_back(new Cannon(getLeftTopCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightBottomCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightTopCannonPosition(position)));

		for (GameObject* child : childObjects)
			entityHandler->registerEntity(child);

		return new StationAI(childObjects);
	}

	void createStationProjectile(const ProjectileParams* const params) const {
		GameObject* projectile = new StationProjectile(params->position /*, SPRITE_PROJECTILE */ );

		configureProjectile(params, projectile);
	}

	void createStationRocket(const ProjectileParams* const params) const {
		GameObject* rocket = new StationProjectile(params->position /*, SPRITE_ROCKET */ );

		configureProjectile(params, rocket);
	}

};