#pragma once

#include <vector>
#include <Entity.h>

#include "Ship.h"
#include "StationAI.h"
#include "EntityHandler.h"
#include "Cannon.h"

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
		GameObject* leftConnector = new GameObject(position, CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);
		GameObject* rightConnector = new GameObject(getRightConnectorPosition(position), CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);
		GameObject* core = new GameObject(getCorePosition(position), CORE_SIZE, TextureAtlas::Station::CORE);
		GameObject* leftNode = new Cannon(getLeftCannonPosition(position));
		GameObject* leftBottomNode = new Cannon(getLeftBottomCannonPosition(position));
		GameObject* leftTopNode = new Cannon(getLeftTopCannonPosition(position));
		GameObject* rightNode = new Cannon(getRightCannonPosition(position));
		GameObject* rightBottomNode = new Cannon(getRightBottomCannonPosition(position));
		GameObject* rightTopNode = new Cannon(getRightTopCannonPosition(position));

		entityHandler->registerEntity(leftConnector);
		entityHandler->registerEntity(rightConnector);
		entityHandler->registerEntity(core);
		entityHandler->registerEntity(leftNode);
		entityHandler->registerEntity(leftBottomNode);
		entityHandler->registerEntity(leftTopNode);
		entityHandler->registerEntity(rightNode);
		entityHandler->registerEntity(rightBottomNode);
		entityHandler->registerEntity(rightTopNode);

		return new StationAI(position);
	}

};