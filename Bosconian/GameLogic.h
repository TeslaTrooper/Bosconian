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
	SoundPlayer soundPlayer;

	vector<StationAI*> stations;
	vector<Formation*> formations;

	bool shipRespawn = false;

	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;
	void checkScoring(const GameObject* const o1, const GameObject* const o2) const;

	void updateStations(float dt) {
		for (int i = 0; i < stations.size(); i++) {
			stations.at(i)->update(dt, entityHandler.getShip());

			if (stations.at(i)->canShootProjectile())
				entititySpawner.spawnStationProjectile(stations.at(i)->getProjectileParams());

			if (stations.at(i)->canShootRocket())
				entititySpawner.spawnStationRocket(stations.at(i)->getRocketParams());

			if (stations.at(i)->inactive())
				stats->gain(SCORE_GAIN_STATION);
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

	void checkForMissingPlayer(float dt) {
		Ship* ship = entititySpawner.checkForMissingPlayer(dt);

		if (ship == nullptr)
			return;

		camera->updateTarget(ship);
		shipRespawn = true;
	}

public:

	GameLogic() : physics(this), entititySpawner(&entityHandler, &soundPlayer), gameWorld(GameWorld(WORLD_WIDTH, WORLD_HEIGHT, WORLD_TYPE_LOOP)) {
		stats = new GameStats();

		Ship* ship = entititySpawner.spawnShip();
		camera = new Camera(ship, WIN_WIDTH - 200, WIN_HEIGHT);

		const vector<StationAI*>& stations = entititySpawner.spawnStations();
		for (StationAI* const station : stations)
			this->stations.push_back(station);

		entititySpawner.spawnObstacles();
	}

	~GameLogic() {};

	void update(float dt) override {
		if (shipRespawn) {
			shipRespawn = false;
			soundPlayer.playBlastOff();
		}

		vector<Entity*> entities = entityHandler.toBaseEntites();
		physics.update(entities, dt);

		updateEntites(dt);
		gameWorld.update(dt, entities);

		entityHandler.cleanupDeadEntities();
		removeInactiveStations();

		checkForMissingPlayer(dt);

		Formation* f = entititySpawner.update(dt);
		if (f != nullptr)
			formations.push_back(f);
	}

	vector<RenderUnit> getRenderUnits() const override;

	void setShipDirection(int direction) const override {
		Ship* ship = entityHandler.getShip();

		if (ship == nullptr || ship->isDestroyed())
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

		soundPlayer.playShipShoot();
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