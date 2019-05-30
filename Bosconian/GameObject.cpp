#include "GameObject.h"

GameObject::GameObject(const Vec2 position, const Vec2 scale, const Rectangle sprite) :
	lifetime(0),
	maxLifetime(0),
	destructionTimeStamp(0),
	destroyed(false),
	canBeCleanedUp(false),
	sprite(sprite) {
	setPosition(position);
	setBbox(scale);

	updateTransformation();
}

void GameObject::update(const float dt) {
	if (canBeCleanedUp)
		return;

	lifetime += dt;
	updateTransformation();
	checkForDestructionAnimation();
}

void GameObject::destroy() {
	if (destroyed)
		return;

	// A marker variable, so that the object
	// knows, how to behave
	destroyed = true;
	// We also need the timestamp in order to
	// to the animation properly
	destructionTimeStamp = lifetime;

	// As we scale the object a little bit for
	// better visual effects, we have to do an
	// adjustment in position
	setPosition(getPosition() - getBbox() / 2);
	setBbox(getBbox() * 2);

	// Also clear movement and acceleration
	setMovement(Vec2());
	setAcceleration(0);
}

void GameObject::checkForDestructionAnimation() {
	if (destroyed && canAnimate()) {
		// Depending, on the passed time since destruction,
		// we calculate based on the duration per sprite,
		// which sprite we have to use out of the explosion
		// animation list
		int n = (int)ceil((lifetime - destructionTimeStamp) / SPRITE_DURATION);

		// Check, if the animation has finished
		// If so, we call afterDestruction
		if (n > 5) {
			afterDestruction();
			return;
		}

		sprite = expMap.at(n);
	}
}

RenderUnit GameObject::getRenderUnit() const {
	return { getTransformation(), sprite };
}

bool GameObject::canCollide() const {
	return true;
}

bool GameObject::canCollideWith(const Entity * const e) const {
	return ((GameObject*) e)->getClassId() != CLASS_ID_GAME_OBJECT;
}

void GameObject::updateTransformation() {
	setTransformation(Mat4::getTransformation(getPosition(), getBbox()));
}

VertexData GameObject::getVertexData() const {
	return ModelData::vertexData;
}

IndexData GameObject::getTriangulatedIndexData() const {
	return ModelData::indexData;
}
