#include "GameLogic.h"

void GameLogic::resolveCollision(Entity * e1, Entity * e2, const Vec2 & location) const {}

vector<RenderUnit> GameLogic::getRenderUnits() const {
	vector<RenderUnit> result;

	vector<GameObject*> objects = entityHandler.getAsList();

	if (objects.size() == 0)
		return result;

	for (GameObject* o : objects)
		result.push_back(o->getRenderUnit());

	return result;
}