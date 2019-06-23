#ifndef ENTITY_SPAWNER
#define ENTITY_SPAWNER

#include "EntityFactory.h"
#include "SoundPlayer.h"

#define OBSTACLE_COUNT 20
#define DEFAULT_SHIP_START_POSITION Vec2(WORLD_WIDTH / 2, WORLD_HEIGHT / 2)
#define ENEMY_SPAWNING_INTERVAL 2
#define ROTATION_ZONE 90
#define PLAYER_CREATION_DELAY 2

class EntitySpawner {

	EntityFactory entityFactory;
	EntityHandler* const entityHandler;
	SoundPlayer* const soundPlayer;

	float lifetime, lastEnemySpawningTimeStamp, shipCreationCtr;
	bool playerIsMissing;

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

			Rectangle obstacle = { (float) rx, (float) ry, IN_GAME_RASTER_SIZE.x, IN_GAME_RASTER_SIZE.y };

			validSpawnPosition = isValidSpawnPosition(obstacle);
		}

		int obstacleType = CustomMath::random(0, 1);
		if (obstacleType == 0)
			entityFactory.createAsteroid(Vec2(rx, ry));
		else
			entityFactory.createMine(Vec2(rx, ry));
	}

	Vec2 getSpawingPoint(const Vec2& playerPosition, const Vec2& playerDirection) const {
		float halfDiagonal = (float) sqrt(pow(MAIN_FRAME_BUFFER_WIDTH, 2) + pow(WIN_HEIGHT, 2)) / 2;

		Mat4 translation = Mat4::translate(playerPosition);
		Mat4 rotation = Mat4::rotateZ((float)CustomMath::random(-ROTATION_ZONE, ROTATION_ZONE));
		
		Vec2 point = playerDirection.norm((float) CustomMath::random((int) halfDiagonal, (int) (halfDiagonal * 1.5f)));

		return translation.mul(rotation).transform(point);
	}

	Formation* doPeriodicEnemySpawning() {
		const GameObject* const ship = entityHandler->getShip();
		const Vec2& shipDirection = ship->getDirection();
		const Vec2& shipPosition = ship->getPosition();

		const Vec2& spawingPoint = getSpawingPoint(shipPosition, shipDirection);

		lastEnemySpawningTimeStamp = lifetime;

		int enemyType = CustomMath::random(0, 32);
		if (enemyType >= 0 && enemyType < 10)
			spawnEnemy1(spawingPoint, ship);
		if (enemyType >= 10 && enemyType < 20)
			spawnEnemy2(spawingPoint, ship);
		if (enemyType >= 20 && enemyType < 22)
			spawnSpy(spawingPoint, ship);
		if (enemyType >= 30)
			return spawnFormation(spawingPoint, entityHandler->getShip());

		return nullptr;
	}

	bool isShipAlive() {
		Ship* s = entityHandler->getShip();

		return s != nullptr && !s->isDestroyed();
	}

public:

	EntitySpawner(EntityHandler* const entityHandler, SoundPlayer* const soundPlayer) : entityHandler(entityHandler), soundPlayer(soundPlayer), entityFactory(entityHandler), 
		lifetime(0), lastEnemySpawningTimeStamp(0), playerIsMissing(false), shipCreationCtr(PLAYER_CREATION_DELAY) {}

	Formation* update(float dt) {
		lifetime += dt;

		if ((lifetime - lastEnemySpawningTimeStamp) > ENEMY_SPAWNING_INTERVAL && isShipAlive())
			return doPeriodicEnemySpawning();

		return nullptr;
	}

	Ship* spawnShip() const {
		return entityFactory.createShip(DEFAULT_SHIP_START_POSITION);
	}

	Ship* checkForMissingPlayer(float dt) {
		if (entityHandler->getShip() == nullptr)
			playerIsMissing = true;

		if (playerIsMissing)
			shipCreationCtr -= dt;

		if (shipCreationCtr <= 0) {
			playerIsMissing = false;
			shipCreationCtr = PLAYER_CREATION_DELAY;
			entityHandler->cleanEnemies();

			return spawnShip();
		}

		return nullptr;
	}

	void spawnObstacles() const {
		for (int i = 0; i < OBSTACLE_COUNT; i++)
			spawnObstacle();
	}

	vector<StationAI*> spawnStations() const {
		vector<StationAI*> stations;

		stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(50, 300)));
		stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION + Vec2(200, 300)));
		stations.push_back(entityFactory.createStation(DEFAULT_SHIP_START_POSITION - Vec2(300, -400)));

		return stations;
	}

	void spawnStationProjectile(const ProjectileParams& params) const {
		entityFactory.createStationProjectile(params);
	}

	void spawnStationRocket(const ProjectileParams& params) const {
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
		soundPlayer->playSpyShipSighted();
	}

	Formation* spawnFormation(const Vec2& position, const GameObject* const player) const {
		return entityFactory.createFormation(position, player);
	}

	void spawnPlayerProjectile(const ProjectileParams& params) const {
		entityFactory.createPlayerProjectile(params);
	}

};

#endif ENTITY_SPAWNER