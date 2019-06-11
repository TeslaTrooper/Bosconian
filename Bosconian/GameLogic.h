#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <stdio.h>
#include <vector>
#include <PhysicsEngine.h>
#include <GameWorld.h>

#include "Game.h"
#include "EntityHandler.h"
#include "Camera.h"
#include "Definitions.h"
#include "EntitySpawner.h"
#include "GameStats.h"

class GameLogic : public Game, public CollisionCallback {

	PhysicsEngine physics;
	EntityHandler entityHandler;
	GameWorld gameWorld;
	EntitySpawner entititySpawner;
	Camera* camera;
	GameStats* stats;
	vector<StationAI*> stations;
	vector<Formation*> formations;

	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;

	void updateStations(float dt) {
		for (int i = 0; i < stations.size(); i++) {
			stations.at(i)->update(dt, entityHandler.getShip());

			if (stations.at(i)->canShootProjectile())
				entititySpawner.spawnStationProjectile(stations.at(i)->getProjectileParams());

			if (stations.at(i)->canShootRocket())
				entititySpawner.spawnStationRocket(stations.at(i)->getRocketParams());

			if (stations.at(i)->inactive())
				stats->gain(1500);
		}
	}

	void updateGameObjects(float dt) {
		vector<GameObject*> objects = entityHandler.getAsList();

		for (int i = 0; i < objects.size(); i++)
			objects.at(i)->update(dt);
	}

	void updateFormations(float dt) {
		for (int i = 0; i < formations.size(); i++)
			formations.at(i)->update(dt);
	}

	void updateEntites(float dt) {
		updateGameObjects(dt);
		updateStations(dt);
		updateFormations(dt);
	}

	void removeInactiveStations() {
		stations.erase(remove_if(stations.begin(), stations.end(),
			[](StationAI* s) { return s->inactive(); }), stations.end());
	}

public:

	GameLogic() : physics(this), entititySpawner(&entityHandler), gameWorld(GameWorld(WORLD_WIDTH, WORLD_HEIGHT, WORLD_TYPE_LOOP)) {
		stats = new GameStats();

		Ship* ship = entititySpawner.spawnShip();
		camera = new Camera(ship, WIN_WIDTH - 200, WIN_HEIGHT);
		const vector<StationAI*>& stations = entititySpawner.spawnStations();
		for (StationAI* const station : stations)
			this->stations.push_back(station);

		entititySpawner.spawnObstacles();
		entititySpawner.spawnEnemy2(DEFAULT_SHIP_START_POSITION - Vec2(200, 100), entityHandler.getShip());

		formations.push_back(entititySpawner.spawnFormation(DEFAULT_SHIP_START_POSITION - Vec2(500, 0), entityHandler.getShip()));
	}

	~GameLogic() {};

	void update(const float dt) override {
		vector<Entity*> entities = entityHandler.toBaseEntites();
		physics.update(entities, dt);

		updateEntites(dt);
		gameWorld.update(dt, entities);

		entityHandler.cleanupDeadEntities();
		removeInactiveStations();
	}

	vector<RenderUnit> getRenderUnits() const override;

	void setShipDirection(int direction) const override {
		Ship* ship = entityHandler.getShip();

		if (ship == nullptr)
			return;

		ship->move(direction);
	}

	void shoot() override {
		Ship* ship = entityHandler.getShip();

		if (ship == nullptr || !ship->canShoot())
			return;

		const Vec2& position = ship->getPosition() + ship->getBbox() / 2;
		const Vec2& direction = ship->getDirection();

		ProjectileParams p = ProjectileParams(position, direction, SHIP_BULLET_SPEED);
		entititySpawner.spawnPlayerProjectile(p);
	}

	Mat4 getCameraTransformation() const override {
		return camera->getTransformation();
	}

	int getScore() const {
		return stats->getScore();
	}

	int getRemainingLifes() override {
		return stats->getRemainingLifes();
	}

	int getLevel() override {
		return stats->getLevel();
	}

};

#endif GAME_LOGIC