#ifndef GAME_OBJECT
#define GAME_OBJECT

#define SPRITE_DURATION 0.1f

#include <Entity.h>
#include <vector>

#include "Definitions.h"

using namespace Rendering;
using namespace TextureAtlas::Explosion;

class GameObject : public Entity {

	float lifetime, maxLifetime, destructionTimeStamp;
	bool destroyed, canBeCleanedUp;
	Rectangle sprite;

	void checkForDestructionAnimation();

public:

	GameObject(const Vec2 position, const Vec2 scale, const Rectangle sprite);

	virtual void update(const float dt);
	RenderUnit getRenderUnit() const;

	virtual bool canCollide() const override;
	virtual bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

	virtual void destroy();
	virtual bool canAnimate() { return true; }
	virtual void afterDestruction() { canBeCleanedUp = true; }

	void markForCleanup() { canBeCleanedUp = true; }
	bool readyForCleanup() { return canBeCleanedUp; }
	bool isDestroyed() { return destroyed; }

	virtual int getClassId() const {
		return CLASS_ID_GAME_OBJECT;
	}

	friend class Ship;
	friend class Cannon;

};

#endif GAME_OBJECT