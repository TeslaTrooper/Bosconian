#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <Entity.h>
#include "Definitions.h"

using namespace Rendering;

class GameObject : public Entity {

	float lifetime, maxLifetime;

	Rectangle sprite;

public:

	GameObject(const Vec2 position, const Vec2 scale, const Rectangle sprite);

	virtual void update(const float dt);
	RenderUnit getRenderUnit() const;

	bool canCollide() const override;
	bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

	virtual int getClassId() const {
		return CLASS_ID_GAME_OBJECT;
	}

	friend class Ship;

};

#endif GAME_OBJECT