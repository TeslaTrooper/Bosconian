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

class GameLogic : public Game, public CollisionCallback {

	PhysicsEngine physics;
	EntityHandler entityHandler;
	GameWorld gameWorld;
	EntitySpawner entititySpawner;
	Camera* camera;
	vector<StationAI*> stations;

	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;

public:

	GameLogic() : physics(this), entititySpawner(&entityHandler), gameWorld(GameWorld(WORLD_WIDTH, WORLD_HEIGHT, WORLD_TYPE_LOOP)) {
		Ship* ship = entititySpawner.spawnShip();
		camera = new Camera(ship, WIN_WIDTH - 200, WIN_HEIGHT);

		stations.push_back(entititySpawner.spawnStations());
		entititySpawner.spawnObstacles();
	};

	~GameLogic() {};

	void update(const float dt) override {
		vector<Entity*> entities = entityHandler.toBaseEntites();
		physics.update(entities, dt);

		vector<GameObject*> objects = entityHandler.getAsList();

		for (int i = 0; i < objects.size(); i++)
			objects.at(i)->update(dt);

		for (int i = 0; i < stations.size(); i++) {
			stations.at(i)->update(dt, entityHandler.getShip()->getPosition());

			if (stations.at(i)->canShoot())
				entititySpawner.spawnStationProjectile(stations.at(i)->getProjectileParams());
		}

		gameWorld.update(dt, entities);

		entityHandler.cleanupDeadEntities();
	};

	vector<RenderUnit> getRenderUnits() const override;

	void setShipDirection(int direction) const override {
		Ship* ship = entityHandler.getShip();

		if (ship == nullptr)
			return;

		ship->move(direction);
	};

	Mat4 getCameraTransformation() const override {
		return camera->getTransformation();
	}

};

#endif GAME_LOGIC