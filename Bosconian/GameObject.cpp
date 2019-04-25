#include "GameObject.h"

GameObject::GameObject(const Vec2 position, const Vec2 scale) : scale(scale) {
	setPosition(position);
}

void GameObject::update(const float dt) {
	lifetime += dt;

	updateTransformation();
}

bool GameObject::canCollide() const {
	return true;
}

bool GameObject::canCollideWith(const Entity * const e) const {
	return true;
}

void GameObject::updateTransformation() {
	setTransformation(Mat4::getTransformation(getPosition(), scale));
}

VertexData GameObject::getVertexData() const {
	return ModelData::vertexData;
}

IndexData GameObject::getTriangulatedIndexData() const {
	return ModelData::indexData;
}
