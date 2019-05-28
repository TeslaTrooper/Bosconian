#include "GameObject.h"

GameObject::GameObject(const Vec2 position, const Vec2 scale, const Rectangle sprite) :
	isAlive(true),
	sprite(sprite) {
	setPosition(position);
	setBbox(scale);

	updateTransformation();
}

void GameObject::update(const float dt) {
	if (!isAlive)
		return;

	lifetime += dt;

	updateTransformation();
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
