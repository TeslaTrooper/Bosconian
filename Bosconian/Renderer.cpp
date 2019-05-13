#include "Renderer.h"

void Renderer::setup(int defaultFramebufferWidth, int defaultFramebufferHeight) {
	BaseOpenGLRenderer::setup(defaultFramebufferWidth, defaultFramebufferHeight);

	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");
	hudShader = ShaderFactory::createShader("hudShader.vert", "hudShader.frag");

	tileset = new Texture("Atlas.bmp", Format::BMP);
	tileset->setAlternativeAlphaColor(ALPHA_COLOR);
	tileset->loadTexture();

	fontset = new Texture("Font.bmp", Format::BMP);
	fontset->setAlternativeAlphaColor(ALPHA_COLOR);
	fontset->loadTexture();

	initProjection();

	mainFrameBuffer = createFrameBuffer(0, 0, MAIN_FRAME_BUFFER_WIDTH, WIN_HEIGHT);
	hudFrameBuffer = createFrameBuffer(MAIN_FRAME_BUFFER_WIDTH, 0, HUD_FRAME_BUFFER_WIDTH, WIN_HEIGHT);

	data = configure(ModelData::quadBindable, DrawMode::TRIANGLES);
}

void Renderer::initProjection() const {
	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, Projection::getOrthographicProjection(MAIN_FRAME_BUFFER_WIDTH, WIN_HEIGHT));

	hudShader->use();
	hudShader->setUniformMatrix4(PROJECTION, Projection::getOrthographicProjection(HUD_FRAME_BUFFER_WIDTH, WIN_HEIGHT));
}

void Renderer::render() const {
	renderEntites();
	renderHUD();

	// Switch to this shader in order to render
	// everthing as a simple flipped texture on a quad
	framebufferShader->use();
}

void Renderer::renderEntites() const {
	vector<RenderUnit> units = game->getRenderUnits();

	tileset->bind();
	bindFrameBuffer(mainFrameBuffer);

	for (int i = 0; i < units.size(); i++) {
		prepareStandardShader(units.at(i));
		draw(data);
	}
}

void Renderer::renderHUD() const {
	fontset->bind();
	bindFrameBuffer(hudFrameBuffer);

	Vec2 scoreLabelPosition = Vec2(100, WIN_HEIGHT - 70);
	prepareHUDShader({ Mat4::getTransformation(scoreLabelPosition, Vec2(100, 20)), TextureAtlas::Font::SCORE });
	draw(data);

	Vec2 scorePosition = Vec2(180, WIN_HEIGHT - 95);
	prepareHUDShader({ Mat4::getTransformation(scorePosition, Vec2(20, 20)), TextureAtlas::Font::ZERO });
	draw(data);

	Vec2 roundLabelPosition = Vec2(0, 50);
	prepareHUDShader({ Mat4::getTransformation(roundLabelPosition, Vec2(100, 20)), TextureAtlas::Font::ROUND });
	draw(data);

	Vec2 roundPosition = Vec2(180, 50);
	prepareHUDShader({ Mat4::getTransformation(roundPosition, Vec2(20, 20)), TextureAtlas::Font::ONE });
	draw(data);
}

void Renderer::prepareStandardShader(const RenderUnit unit) const {
	Mat3 textureTransformation = getTextureCoordinates(unit.textureTransform);

	standardShader->use();
	standardShader->setUniformMatrix4(TRANSFORM, unit.transformation);
	standardShader->setUniformMatrix3(TEXTURE_TRANSFORM, textureTransformation);
	standardShader->setUniformMatrix4(VIEW, game->getCameraTransformation());
}

void Renderer::prepareHUDShader(const RenderUnit unit) const {
	Mat3 textureTransformation = getTextureCoordinates(unit.textureTransform);

	hudShader->use();
	hudShader->setUniformMatrix4(TRANSFORM, unit.transformation);
	hudShader->setUniformMatrix3(TEXTURE_TRANSFORM, textureTransformation);
}

Mat3 Renderer::getTextureCoordinates(const Rectangle rect) const {
	Mat3 transformation;

	Vec2 textureTranslator = Vec2(rect.position.x * RASTER_SIZE, rect.position.y * RASTER_SIZE);
	transformation.translate(textureTranslator);

	Vec2 textureScaler = Vec2(rect.size.x * RASTER_SIZE, rect.size.y * RASTER_SIZE);
	transformation.scale(textureScaler);

	return transformation;
}

Renderer::~Renderer() {
	delete standardShader;
	delete framebufferShader;
	delete hudShader;
	delete tileset;
	delete fontset;
}