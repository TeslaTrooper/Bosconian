#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <Entity.h>
#include <vector>

#include "Definitions.h"

using namespace Rendering;

class GameObject : public Entity {

	float lifetime, maxLifetime;
	bool isAlive;
	Rectangle sprite;

public:

	GameObject(const Vec2 position, const Vec2 scale, const Rectangle sprite);

	virtual void update(const float dt);
	RenderUnit getRenderUnit() const;

	virtual bool canCollide() const override;
	virtual bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

	void die() { isAlive = false; };
	bool isDead() { return !isAlive; };

	virtual int getClassId() const {
		return CLASS_ID_GAME_OBJECT;
	}

	friend class Ship;
	friend class Cannon;

};

#endif GAME_OBJECT