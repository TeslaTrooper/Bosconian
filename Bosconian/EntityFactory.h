#pragma once

#include <vector>
#include <Entity.h>

#include "Ship.h"
#include "StationAI.h"
#include "EntityHandler.h"
#include "Cannon.h"
#include "StationProjectile.h"

#define OBSTACLE_SIZE Vec2(40, 40)

#define CORE_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 1)
#define CONNECTOR_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 3)

using namespace Station;

class EntityFactory {

	EntityHandler* const entityHandler;

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
		vector<Cannon*> childObjects;

		GameObject* leftConnector = new GameObject(position, CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);
		GameObject* rightConnector = new GameObject(getRightConnectorPosition(position), CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);
		GameObject* core = new GameObject(getCorePosition(position), CORE_SIZE, TextureAtlas::Station::CORE);
		childObjects.push_back(new Cannon(getLeftCannonPosition(position)));
		childObjects.push_back(new Cannon(getLeftBottomCannonPosition(position)));
		childObjects.push_back(new Cannon(getLeftTopCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightBottomCannonPosition(position)));
		childObjects.push_back(new Cannon(getRightTopCannonPosition(position)));

		// We do not need those objects inside the StationAI
		// So we leave them out of the list of child objects
		entityHandler->registerEntity(leftConnector);
		entityHandler->registerEntity(rightConnector);
		entityHandler->registerEntity(core);

		for (GameObject* child : childObjects)
			entityHandler->registerEntity(child);

		return new StationAI(childObjects);
	}

	void createStationProjectile(const ProjectileParams* const params) const {
		GameObject* projectile = new StationProjectile(params->position);

		projectile->setVMax(params->direction.length());
		projectile->setAcceleration(params->direction.length());
		projectile->setDirection(params->direction.norm());
		projectile->setMovement(params->direction);

		entityHandler->registerEntity(projectile);
	}

};