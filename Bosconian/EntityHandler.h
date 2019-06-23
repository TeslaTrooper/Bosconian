#pragma once

#include <vector>
#include <map>

#include "Ship.h"

class EntityHandler {

	map<int, vector<GameObject*>*> objects;

	bool hasElements(int key) const {
		return objects.at(key)->size() > 0;
	}

	void removeIfPresent(vector<GameObject*>* const list, const GameObject* const entity) const {
		auto iterator = find(list->begin(), list->end(), entity);

		if (iterator != list->end())
			list->erase(iterator);
	}

	void deRegisterEntity(GameObject* const entity) const {
		vector<GameObject*>* list = objects.at(entity->getClassId());

		removeIfPresent(list, entity);
	}

	void deRegisterEntityByClassType(int type) const {
		if (!hasElements(type))
			return;

		vector<GameObject*>* list = objects.at(type);
		for (int i = 0; i < list->size(); i++)
			deRegisterEntity(list->at(i));
	}

public:

	EntityHandler() {
		objects[CLASS_ID_GAME_OBJECT] = new vector<GameObject*>();
		objects[CLASS_ID_SHIP] = new vector<GameObject*>();
		objects[CLASS_ID_CANNON] = new vector<GameObject*>();
		objects[CLASS_ID_STATION_PROJECTILE] = new vector<GameObject*>();
		objects[CLASS_ID_ENEMY_TYPE_1] = new vector<GameObject*>();
		objects[CLASS_ID_ENEMY_TYPE_2] = new vector<GameObject*>();
		objects[CLASS_ID_ENEMY_TYPE_SPY] = new vector<GameObject*>();
		objects[CLASS_ID_ASTEROID] = new vector<GameObject*>();
		objects[CLASS_ID_MINE] = new vector<GameObject*>();
		objects[CLASS_ID_SHIP_PROJECTILE] = new vector<GameObject*>();
		objects[CLASS_ID_STATION_CORE] = new vector<GameObject*>();
		objects[CLASS_ID_STATION_CONNECTOR] = new vector<GameObject*>();
	}

	GameObject* registerEntity(GameObject* const entity) {
		int key = entity->getClassId();
		objects.at(key)->push_back(entity);

		return entity;
	}

	void cleanupDeadEntities() const {
		for (const pair<int, vector<GameObject*>*> pair : objects)
			for (int i = 0; i < pair.second->size(); i++)
				if (pair.second->at(i)->readyForCleanup())
					deRegisterEntity(pair.second->at(i));
	}

	void cleanEnemies() const {
		deRegisterEntityByClassType(CLASS_ID_ENEMY_TYPE_1);
		deRegisterEntityByClassType(CLASS_ID_ENEMY_TYPE_2);
		deRegisterEntityByClassType(CLASS_ID_ENEMY_TYPE_SPY);
	}

	vector<Entity*> toBaseEntites() const {
		vector<Entity*> entities;

		for (const pair<int, vector<GameObject*>*> pair : objects)
			for (int i = 0; i < pair.second->size(); i++)
				entities.push_back((Entity*) pair.second->at(i));

		return entities;
	}

	vector<GameObject*> getAsList() const {
		vector<GameObject*> result;

		for (const pair<int, vector<GameObject*>*> pair : objects)
			for (int i = 0; i < pair.second->size(); i++)
				result.push_back(pair.second->at(i));

		return result;
	}

	Ship* getShip() const {
		if (hasElements(CLASS_ID_SHIP))
			return (Ship*) objects.at(CLASS_ID_SHIP)->at(0);

		return nullptr;
	}

	bool spyExists() const {
		return hasElements(CLASS_ID_ENEMY_TYPE_SPY);
	}

};