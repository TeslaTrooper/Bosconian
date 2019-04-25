#include "Renderer.h"

void Renderer::setup() {
	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");
	tileset = new Texture("Atlas.bmp", Format::BMP);
	tileset->setAlternativeAlphaColor(new Color(141, 0, 200));
	tileset->loadTexture();

	initProjection();
	createFrameBuffer(WIN_WIDTH, WIN_HEIGHT);
	data = configure(ModelData::quadBindable, DrawMode::TRIANGLES);
}

void Renderer::initProjection() const {
	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, Projection::getOrthographicProjection(WIN_WIDTH, WIN_HEIGHT));
}

void Renderer::render() const {
	vector<RenderUnit> units = game->getRenderUnits();

	tileset->bind();
	for (int i = 0; i < units.size(); i++) {
		prepareShaders(units.at(i));
		draw(data);
	}

	framebufferShader->use();
}

void Renderer::prepareShaders(const RenderUnit unit) const {
	Mat3 textureTransformation = getTextureCoordinates(unit.textureTransform);

	this->standardShader->use();
	this->standardShader->setUniformMatrix4(TRANSFORM, unit.transformation);
	this->standardShader->setUniformMatrix3(TEXTURE_TRANSFORM, textureTransformation);
}

Mat3 Renderer::getTextureCoordinates(const Rectangle rect) const {
	Mat3 transformation;

	Vec2 textureTranslator = Vec2(rect.position.x * RASTER_SIZE / tileset->getWidth(), rect.position.y * RASTER_SIZE / tileset->getHeight());
	transformation.translate(textureTranslator);

	Vec2 textureScaler = Vec2(rect.size.x * RASTER_SIZE / tileset->getWidth(), rect.size.y * RASTER_SIZE / tileset->getHeight());
	transformation.scale(textureScaler);

	return transformation;
}

Renderer::~Renderer() {
	delete standardShader;
	delete framebufferShader;
}