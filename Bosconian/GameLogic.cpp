#include "GameLogic.h"

void GameLogic::resolveCollision(Entity * e1, Entity * e2, const Vec2& location) const {
	GameObject* o1 = (GameObject*) e1;
	GameObject* o2 = (GameObject*) e2;

	if (o1->getClassId() == CLASS_ID_GAME_OBJECT)
		o1->die();
	else if (o2->getClassId() == CLASS_ID_GAME_OBJECT)
		o2->die();
}

vector<RenderUnit> GameLogic::getRenderUnits() const {
	vector<RenderUnit> result;

	vector<GameObject*> objects = entityHandler.getAsList();

	if (objects.size() == 0)
		return result;

	for (GameObject* o : objects)
		result.push_back(o->getRenderUnit());

	return result;
}