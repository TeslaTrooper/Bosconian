#ifndef ENEMY
#define ENEMY

#include "GameObject.h"

class Enemy : public GameObject {

	const int enemyType;
	const GameObject* const player;
	float lastDirectionChangeTimeStamp;

	const map<int, vector<Vec2>> quadrantDirectionMap = {
		{ QUADRANT_RIGHT_TOP,		{ VECTOR_UP, VECTOR_RIGHT_UP, VECTOR_RIGHT } },
		{ QUADRANT_LEFT_TOP,		{ VECTOR_UP, VECTOR_LEFT_UP, VECTOR_LEFT } },
		{ QUADRANT_LEFT_BOTTOM,		{ VECTOR_LEFT, VECTOR_LEFT_DOWN, VECTOR_DOWN } },
		{ QUADRANT_RIGHT_BOTTOM,	{ VECTOR_RIGHT, VECTOR_RIGHT_DOWN, VECTOR_DOWN } }
	};

	int determineQuadrant() const {
		const Vec2& p = player->getPosition();
		const Vec2& e = getPosition();

		if (p.x >= e.x && p.y > e.y)
			return QUADRANT_RIGHT_TOP;

		if (p.x < e.x && p.y >= e.y)
			return QUADRANT_LEFT_TOP;

		if (p.x <= e.x && p.y < e.y)
			return QUADRANT_LEFT_BOTTOM;

		return QUADRANT_RIGHT_BOTTOM;
	}

	const vector<Vec2>& getPossibleDirections(int quadrant) const {
		return quadrantDirectionMap.at(quadrant);
	}

	const vector<float> calculateSimilarityBetween(const Vec2& reference, const vector<Vec2>& directions) const {
		vector<float> values;

		for (const Vec2& v : directions)
			values.push_back(reference.x * v.x + reference.y * v.y);

		return values;
	}

	int getGreatestValueIndexOf(const vector<float>& values) const {
		int resultIndex = 0;

		for (int i = 0; i < values.size(); i++)
			if (values.at(i) > values.at(resultIndex))
				resultIndex = i;

		return resultIndex;
	}

	void changeSpriteToDirection(int quadrant, int greatestValueIndex) {
		if (enemyType == 1)
			sprite = TextureAtlas::Enemy1::spriteMap.at(quadrant).at(greatestValueIndex);

		if (enemyType == 2)
			sprite = TextureAtlas::Enemy2::spriteMap.at(quadrant).at(greatestValueIndex);

		if (enemyType == 3)
			sprite = TextureAtlas::Spy::spriteMap.at(quadrant).at(greatestValueIndex);
	}

	void calcDirectionToPlayer() {
		// Problem:	Enemy should constantly move towards player.
		//			We have 8 possible directions an object can move along.
		//			Depending on player and enemy position,
		//			we have to determine the -best- direction

		// 1. Determine quadrant, in which player position lies
		//    Origin gets represented through enemy position
		const int quadrant = determineQuadrant();

		// 2. Calculate exact direction to player position
		//	  as reference for later calculations
		//	  For the sake of simplicity, we only consider
		//	  normalized vectors
		const Vec2 referenceDirection = (player->getPosition() - getPosition()).norm();

		// 3. Based on quadrant, there are only 3 possible
		//	  directions left, which make sense to move along.
		const vector<Vec2>& possibleDirections = getPossibleDirections(quadrant);

		// 4. For each direction, we have to calculate the
		//    similarity between a possible direction and referenceDirection
		const vector<float>& similarities = calculateSimilarityBetween(referenceDirection, possibleDirections);

		// 5. Based on those simmilarity values, we can choose
		//	  the direction, which has the greatest similarity 
		//	  What we actually need, is the index of the greatest
		//	  value of similarities array.
		int greatestValueIndex = getGreatestValueIndexOf(similarities);

		// 6. This index can now be used to choose the -best- direction
		//	  out of the 3 possible directions
		setDirection(possibleDirections.at(greatestValueIndex));
		setMovement(possibleDirections.at(greatestValueIndex).norm(ENEMY_SPEED));
		changeSpriteToDirection(quadrant, greatestValueIndex);
	}

public:

	Enemy(const Vec2& position, int enemyType, const GameObject* const player) :
		GameObject(position, IN_GAME_RASTER_SIZE, TextureAtlas::Enemy1::SPRITE_UP), player(player), enemyType(enemyType) {
		setVMax(ENEMY_SPEED);
		setAcceleration(ENEMY_SPEED);
	}

	void update(float dt) override {
		GameObject::update(dt);

		if (destroyed || player == nullptr || player->isDestroyed())
			return;

		if ((lifetime - lastDirectionChangeTimeStamp) < ENEMY_DIRECTION_CHANGE_INTERVAL)
			return;

		lastDirectionChangeTimeStamp = lifetime;

		calcDirectionToPlayer();
	}

	bool canCollideWith(const Entity* const e) const override {
		int id = ((GameObject*) e)->getClassId();

		// Can collide with ship / projetile / obstacles
		return id != CLASS_ID_CANNON && id != CLASS_ID_STATION_CONNECTOR &&
			id != CLASS_ID_STATION_CORE && id != CLASS_ID_STATION_PROJECTILE &&
			id != CLASS_ID_ENEMY_TYPE_1 && id != CLASS_ID_ENEMY_TYPE_2 && id != CLASS_ID_ENEMY_TYPE_SPY;
	}

	int getClassId() const override {
		if (enemyType == ENEMY_TYPE_1)
			return CLASS_ID_ENEMY_TYPE_1;

		if (enemyType == ENEMY_TYPE_2)
			return CLASS_ID_ENEMY_TYPE_2;

		return CLASS_ID_ENEMY_TYPE_SPY;
	}

};

#endif ENEMY