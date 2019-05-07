#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <stdio.h>
#include <vector>
#include <PhysicsEngine.h>

#include "Game.h"
#include "EntityFactory.h"
#include "EntityHandler.h"
#include "Camera.h"
#include "Definitions.h"

#define WORLD_WIDTH		600
#define WORLD_HEIGHT	1000

#define DEFAULT_SHIP_START_POSITION Vec2(300, 500)

class GameLogic : public Game, public CollisionCallback {

	PhysicsEngine physics;
	EntityFactory entityFactory;
	EntityHandler entityHandler;
	Camera* camera;

	void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const override;

public:

	GameLogic() : physics(this), entityFactory(&entityHandler) {
		Ship* ship = entityFactory.createShip(DEFAULT_SHIP_START_POSITION);
		entityFactory.createMine(Vec2(50, 50));
		entityFactory.createStation(Vec2(70, 100));

		camera = new Camera(ship, WIN_WIDTH, WIN_HEIGHT);
	};
	~GameLogic() {};

	void update(const float dt) override {
		vector<Entity*> entities = entityHandler.toBaseEntites();
		physics.update(entities, dt);

		vector<GameObject*> objects = entityHandler.getAsList();

		for (int i = 0; i < objects.size(); i++)
			objects.at(i)->update(dt);
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