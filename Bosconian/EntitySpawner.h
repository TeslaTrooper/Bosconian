#ifndef ENTITY_SPAWNER
#define ENTITY_SPAWNER

#include "EntityFactory.h"

#define OBSTACLE_COUNT 100
#define DEFAULT_SHIP_START_POSITION Vec2(WORLD_WIDTH / 2, WORLD_HEIGHT / 2)

class EntitySpawner {

	EntityFactory entityFactory;
	EntityHandler* const entityHandler;

	bool isValidSpawnPosition(const Rectangle& rect) {
		vector<GameObject*> objects = entityHandler->getAsList();

		for (const GameObject* const obj : objects) {
			Vec2 position = obj->getPosition();
			Vec2 bbox = obj->getBbox();

			Rectangle r = { position.x, position.y, bbox.x, bbox.y };

			if (rect.intersects(r))
				return false;
		}

		return true;
	}

	void spawnObstacle() {
		bool validSpawnPosition = false;

		int rx = 0, ry = 0;
		while (!validSpawnPosition) {
			rx = CustomMath::random(0, WORLD_WIDTH);
			ry = CustomMath::random(0, WORLD_HEIGHT);

			Rectangle obstacle = { (float) rx, (float) ry, 50.f, 50.f };

			validSpawnPosition = isValidSpawnPosition(obstacle);
		}

		int obstacleType = CustomMath::random(0, 1);
		if (obstacleType == 0)
			entityFactory.createAsteroid(Vec2(rx, ry));
		else
			entityFactory.createMine(Vec2(rx, ry));
	}

public:

	EntitySpawner(EntityHandler* const entityHandler) : entityHandler(entityHandler), entityFactory(entityHandler) {}

	Ship* spawnShip() {
		return entityFactory.createShip(DEFAULT_SHIP_START_POSITION);
	}

	void spawnObstacles() {
		for (int i = 0; i < OBSTACLE_COUNT; i++)
			spawnObstacle();
	};

	void spawnStations() {
		entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(50, 150));
	};

};

#endif ENTITY_SPAWNER