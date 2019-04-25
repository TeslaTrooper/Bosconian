#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <Entity.h>
#include "Definitions.h"

class GameObject : public Entity {

	float lifetime, maxLifetime;
	const Vec2 scale;

public:

	GameObject(const Vec2 position, const Vec2 scale);

	virtual void update(const float dt);

	bool canCollide() const override;
	bool canCollideWith(const Entity* const e) const override;
	void updateTransformation() override;
	VertexData getVertexData() const override;
	IndexData getTriangulatedIndexData() const override;

};

#endif GAME_OBJECT