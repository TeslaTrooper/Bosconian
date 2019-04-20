#include "Renderer.h"

void Renderer::setup() {
	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");

	initProjection();
	createFrameBuffer(WIN_WIDTH, WIN_HEIGHT);
}

void Renderer::initProjection() const {
	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, Projection::getOrthographicProjection(WIN_WIDTH, WIN_HEIGHT));
}

void Renderer::render() const {}

Renderer::~Renderer() {
	delete standardShader;
	delete framebufferShader;
}