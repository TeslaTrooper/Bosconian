#include "Renderer.h"

void Renderer::setup() {
	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");
	tileset = new Texture("Atlas.bmp", Format::BMP);
	tileset->setAlternativeAlphaColor(new Color(141, 0, 200));
	tileset->loadTexture();

	initProjection();
	createFrameBuffer(0, 0, WIN_WIDTH, WIN_HEIGHT);
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
	this->standardShader->setUniformMatrix4(VIEW, game->getCameraTransformation());
	this->standardShader->setVector2(TEXTURE_ROTATION_PIVOT, getTextureRotationPivot(unit.textureTransform));
}

Mat3 Renderer::getTextureCoordinates(const Rectangle rect) const {
	Mat3 transformation;

	Vec2 textureTranslator = Vec2(rect.position.x * RASTER_SIZE, rect.position.y * RASTER_SIZE);
	transformation.translate(textureTranslator);

	Vec2 textureScaler = Vec2(rect.size.x * RASTER_SIZE, rect.size.y * RASTER_SIZE);
	transformation.scale(textureScaler);

	return transformation;
}

Vec2 Renderer::getTextureRotationPivot(const Rectangle rect) const {
	Vec2 pixelPosition = rect.position * RASTER_SIZE;
	Vec2 pixelSize = rect.size * RASTER_SIZE;

	return pixelPosition + (pixelSize / 2);
}

Renderer::~Renderer() {
	delete standardShader;
	delete framebufferShader;
	delete tileset;
}