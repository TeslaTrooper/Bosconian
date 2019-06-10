#ifndef ENTITY_SPAWNER
#define ENTITY_SPAWNER

#include "EntityFactory.h"

#define OBSTACLE_COUNT 20
#define DEFAULT_SHIP_START_POSITION Vec2(WORLD_WIDTH / 2, WORLD_HEIGHT / 2)

class EntitySpawner {

	EntityFactory entityFactory;
	EntityHandler* const entityHandler;

	bool isValidSpawnPosition(const Rectangle& rect) const {
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

	void spawnObstacle() const {
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

	Ship* spawnShip() const {
		return entityFactory.createShip(DEFAULT_SHIP_START_POSITION);
	}

	void spawnObstacles() const {
		for (int i = 0; i < OBSTACLE_COUNT; i++)
			spawnObstacle();
	}

	vector<StationAI*> spawnStations() const {
		vector<StationAI*> stations;

		stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(50, 300)));
		//stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(200, 300)));
		//stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(100, 400)));

		return stations;
	}

	void spawnStationProjectile(const ProjectileParams* const params) const {
		entityFactory.createStationProjectile(params);
	}

	void spawnStationRocket(const ProjectileParams* const params) const {
		entityFactory.createStationRocket(params);
	}

	void spawnEnemy1(const Vec2& position, const GameObject* const player) const {
		entityFactory.createEnemy1(position, player);
	}

	void spawnEnemy2(const Vec2& position, const GameObject* const player) const {
		entityFactory.createEnemy2(position, player);
	}

	void spawnSpy(const Vec2& position, const GameObject* const player)const {
		entityFactory.createSpy(position, player);
	}

	Formation* spawnFormation(const Vec2& position, const GameObject* const player) const {
		return entityFactory.createFormation(position, player);
	}

};

#endif ENTITY_SPAWNER