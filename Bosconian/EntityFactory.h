#pragma once

#include <vector>
#include <Entity.h>

#include "Ship.h"
#include "EntityHandler.h"

class EntityFactory {

	EntityHandler* const entityHandler;

public:

	EntityFactory(EntityHandler* const entityHandler) :
		entityHandler(entityHandler) {}

	
	Ship* createShip(const Vec2& position, const Vec2& scale) {
		Ship* ship = new Ship(position, scale);

		ship->setVMax(100);
		ship->setAcceleration(100);
		ship->setDirection(Vec2(0, 1));

		return (Ship*) entityHandler->registerEntity(ship);
	}

	GameObject* createAsteroid(const Vec2& position, const Vec2& scale) {
		GameObject* asteroid = new GameObject(position, scale, TextureAtlas::Asteroid::SPRITE);

		asteroid->setVMax(0);
		asteroid->setAcceleration(0);

		return entityHandler->registerEntity(asteroid);
	}

	GameObject* createMine(const Vec2& position, const Vec2& scale) {
		GameObject* mine = new GameObject(position, scale, TextureAtlas::Mine::SPRITE);

		mine->setVMax(0);
		mine->setAcceleration(0);

		return entityHandler->registerEntity(mine);
	}

};