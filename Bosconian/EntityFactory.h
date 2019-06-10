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
#include "Enemy.h"
#include "Obstacle.h"
#include "Formation.h"
#include "Member.h"

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
		GameObject* asteroid = new Obstacle(position, TextureAtlas::Obstacle::ASTEROID);

		asteroid->setVMax(0);
		asteroid->setAcceleration(0);

		return entityHandler->registerEntity(asteroid);
	}

	GameObject* createMine(const Vec2& position) const {
		GameObject* mine = new Obstacle(position, TextureAtlas::Obstacle::MINE);

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
		GameObject* projectile = new StationProjectile(params->position, IN_GAME_RASTER_SIZE / 4, TextureAtlas::Missile::BULLET );

		configureProjectile(params, projectile);
	}

	void createStationRocket(const ProjectileParams* const params) const {
		const Rendering::Rectangle* sprite;

		if (params->direction.y > 0)
			sprite = &TextureAtlas::Missile::ROCKET_UP_WARDS;
		else
			sprite = &TextureAtlas::Missile::ROCKET_DOWN_WARDS;

		GameObject* rocket = new StationProjectile(params->position, IN_GAME_RASTER_SIZE, *sprite );
		configureProjectile(params, rocket);
	}

	void createEnemy1(const Vec2& position, const GameObject* const player) const {
		entityHandler->registerEntity(new Enemy(position, ENEMY_TYPE_1, player));
	}

	void createEnemy2(const Vec2& position, const GameObject* const player) const {
		entityHandler->registerEntity(new Enemy(position, ENEMY_TYPE_2, player));
	}

	void createSpy(const Vec2& position, const GameObject* const player) const {
		entityHandler->registerEntity(new Enemy(position, ENEMY_TYPE_SPY, player));
	}

	Formation* createFormation(const Vec2& position, const GameObject* const player) const {
		GameObject* leader = new Enemy(position, ENEMY_TYPE_1, player);

		vector<Member*> formationMembers;
		formationMembers.push_back(new Member(position - Vec2(75, 0), ENEMY_TYPE_1, player));
		formationMembers.push_back(new Member(position + Vec2(75, 0), ENEMY_TYPE_1, player));
		formationMembers.push_back(new Member(position - Vec2(0, 75), ENEMY_TYPE_1, player));
		formationMembers.push_back(new Member(position + Vec2(0, 75), ENEMY_TYPE_1, player));

		for (GameObject* const o : formationMembers)
			entityHandler->registerEntity(o);

		entityHandler->registerEntity(leader);

		return new Formation(leader, formationMembers);
	}

};