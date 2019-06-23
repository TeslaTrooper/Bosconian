#include "GameLogic.h"

void GameLogic::checkScoring(const GameObject* const o1, const GameObject* const o2) const {
	int classIdO1 = o1->getClassId();
	int classIdO2 = o2->getClassId();

	// Cannon
	if (classIdO1 == CLASS_ID_CANNON && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_CANNON);

	if (classIdO2 == CLASS_ID_CANNON && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_CANNON);

	// Asteroid
	if (classIdO1 == CLASS_ID_ASTEROID && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_ASTEROID);

	if (classIdO2 == CLASS_ID_ASTEROID && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_ASTEROID);

	// Mine
	if (classIdO1 == CLASS_ID_MINE && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_MINE);

	if (classIdO2 == CLASS_ID_MINE && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_MINE);

	// Station Projectile
	if (classIdO1 == CLASS_ID_STATION_PROJECTILE && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_STATION_PROJECTILE);

	if (classIdO2 == CLASS_ID_STATION_PROJECTILE && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_STATION_PROJECTILE);

	// Enemy 1
	if (classIdO1 == CLASS_ID_ENEMY_TYPE_1 && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_1);

	if (classIdO2 == CLASS_ID_ENEMY_TYPE_1 && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_1);

	// Enemy 2
	if (classIdO1 == CLASS_ID_ENEMY_TYPE_2 && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_2);

	if (classIdO2 == CLASS_ID_ENEMY_TYPE_2 && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_2);

	// Enemy Spy
	if (classIdO1 == CLASS_ID_ENEMY_TYPE_SPY && !o1->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_SPY);

	if (classIdO2 == CLASS_ID_ENEMY_TYPE_SPY && !o2->isDestroyed())
		stats->gain(SCORE_GAIN_ENEMY_TYPE_SPY);
}

void GameLogic::resolveCollision(Entity * e1, Entity * e2, const Vec2& location) const {
	GameObject* o1 = (GameObject*) e1;
	GameObject* o2 = (GameObject*) e2;

	checkScoring(o1, o2);

	// Destroy both objects
	o1->destroy();
	o2->destroy();

	if (o1->getClassId() == CLASS_ID_SHIP || o2->getClassId() == CLASS_ID_SHIP)
		stats->decreaseRemainingLifes();

	if (o1->getClassId() == CLASS_ID_STATION_CORE || o2->getClassId() == CLASS_ID_STATION_CORE)
		soundPlayer.playBigExplosion();
	else
		soundPlayer.playSmallExplosion();
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