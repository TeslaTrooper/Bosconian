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
#include "PlayerProjectile.h"

class EntityFactory {

	EntityHandler* const entityHandler;

	void configureProjectile(const ProjectileParams& params, GameObject* const object) const {
		object->setVMax(params.speed);
		object->setAcceleration(params.speed);
		object->setDirection(params.direction);
		object->setMovement(params.direction.mul(params.speed));

		entityHandler->registerEntity(object);
	}

public:

	EntityFactory(EntityHandler* const entityHandler) :
		entityHandler(entityHandler) {}

	
	Ship* createShip(const Vec2& position) const {
		Ship* ship = new Ship(position);

		ship->setVMax(SHIP_SPEED);
		ship->setAcceleration(SHIP_SPEED);
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

	void createStationProjectile(const ProjectileParams& params) const {
		GameObject* projectile = new StationProjectile(params.position, IN_GAME_RASTER_SIZE / 4, TextureAtlas::Missile::BULLET );

		configureProjectile(params, projectile);
	}

	void createStationRocket(const ProjectileParams& params) const {
		const Rendering::Rectangle* sprite;

		if (params.direction.y > 0)
			sprite = &TextureAtlas::Missile::ROCKET_UP_WARDS;
		else
			sprite = &TextureAtlas::Missile::ROCKET_DOWN_WARDS;

		GameObject* rocket = new StationProjectile(params.position, IN_GAME_RASTER_SIZE, *sprite );
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

	void createPlayerProjectile(const ProjectileParams& params) const {
		float angle = 0;

		if (params.direction == VECTOR_DOWN || params.direction == VECTOR_UP)
			angle = 90;
		if (params.direction == VECTOR_LEFT_DOWN || params.direction == VECTOR_RIGHT_UP)
			angle = 45;
		if (params.direction == VECTOR_RIGHT_DOWN || params.direction == VECTOR_LEFT_UP)
			angle = -45;

		GameObject* projectile1 = new PlayerProjectile(params.position, angle);
		GameObject* projectile2 = new PlayerProjectile(params.position, angle);
		ProjectileParams p = ProjectileParams(params.position, params.direction.inv(), params.speed);

		configureProjectile(params, projectile1);
		configureProjectile(p, projectile2);
	}

};