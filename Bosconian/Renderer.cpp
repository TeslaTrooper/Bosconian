#include "Renderer.h"

void Renderer::render() const {}

void Renderer::setup() {}

Renderer::~Renderer() {
	delete game;
}