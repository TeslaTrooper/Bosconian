#pragma once

#include <vector>
#include <Entity.h>

#include "Ship.h"
#include "EntityHandler.h"

#define OBSTACLE_SIZE Vec2(40, 40)
#define CORE_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 1)
#define CONNECTOR_SIZE IN_GAME_RASTER_SIZE * Vec2(2, 3)

class EntityFactory {

	EntityHandler* const entityHandler;

public:

	EntityFactory(EntityHandler* const entityHandler) :
		entityHandler(entityHandler) {}

	
	Ship* createShip(const Vec2& position) {
		Ship* ship = new Ship(position);

		ship->setVMax(100);
		ship->setAcceleration(100);
		ship->setDirection(Vec2(0, 1));

		return (Ship*) entityHandler->registerEntity(ship);
	}

	GameObject* createAsteroid(const Vec2& position) {
		GameObject* asteroid = new GameObject(position, OBSTACLE_SIZE, TextureAtlas::Obstacle::ASTEROID);

		asteroid->setVMax(0);
		asteroid->setAcceleration(0);

		return entityHandler->registerEntity(asteroid);
	}

	GameObject* createMine(const Vec2& position) {
		GameObject* mine = new GameObject(position, OBSTACLE_SIZE, TextureAtlas::Obstacle::MINE);

		mine->setVMax(0);
		mine->setAcceleration(0);

		return entityHandler->registerEntity(mine);
	}

	void createStation(const Vec2& position) {
		GameObject* leftConnector = new GameObject(position, CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);

		Vec2 rightConnectorPosition = position + Vec2(130, 0);
		GameObject* rightConnector = new GameObject(rightConnectorPosition, CONNECTOR_SIZE, TextureAtlas::Station::CONNECTORS);

		Vec2 corePosition = position + Vec2(65, 50);
		GameObject* core = new GameObject(corePosition, CORE_SIZE, TextureAtlas::Station::CORE);

		Vec2 leftNodePosition = position + Vec2(-25, 50);
		GameObject* leftNode = new GameObject(leftNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		Vec2 leftBottomNodePosition = position + Vec2(25, -25);
		GameObject* leftBottomNode = new GameObject(leftBottomNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		Vec2 leftTopNodePosition = position + Vec2(25, 125);
		GameObject* leftTopNode = new GameObject(leftTopNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		Vec2 rightNodePosition = position + Vec2(205, 50);
		GameObject* rightNode = new GameObject(rightNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		Vec2 rightBottomNodePosition = position + Vec2(155, -25);
		GameObject* rightBottomNode = new GameObject(rightBottomNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		Vec2 rightTopNodePosition = position + Vec2(155, 125);
		GameObject* rightTopNode = new GameObject(rightTopNodePosition, IN_GAME_RASTER_SIZE, TextureAtlas::Station::NODE);

		entityHandler->registerEntity(core);
		entityHandler->registerEntity(leftConnector);
		entityHandler->registerEntity(leftNode);
		entityHandler->registerEntity(rightConnector);
		entityHandler->registerEntity(leftBottomNode);
		entityHandler->registerEntity(leftTopNode);
		entityHandler->registerEntity(rightNode);
		entityHandler->registerEntity(rightBottomNode);
		entityHandler->registerEntity(rightTopNode);
	}

};