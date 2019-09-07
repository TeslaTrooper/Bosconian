#include "Renderer.h"

void Renderer::setup(int defaultFramebufferWidth, int defaultFramebufferHeight) {
	BaseRenderer::setup(defaultFramebufferWidth, defaultFramebufferHeight);

	standardShader = ShaderFactory::createShader("shader.vert", "shader.frag");
	framebufferShader = ShaderFactory::createShader("framebufferShader.vert", "framebufferShader.frag");
	hudShader = ShaderFactory::createShader("hudShader.vert", "shader.frag");
	backgroundShader = ShaderFactory::createShader("hudShader.vert", "backgroundShader.frag");
	radarShader = ShaderFactory::createShader("radarShader.vert", "radarShader.frag");

	background = new Texture("bg.bmp", Format::BMP);
	background->loadTexture();

	tileset = new Texture("Atlas.bmp", Format::BMP);
	tileset->setAlternativeAlphaColor(ALPHA_COLOR);
	tileset->loadTexture();

	fontset = new Texture("Font.bmp", Format::BMP);
	fontset->setAlternativeAlphaColor(ALPHA_COLOR);
	fontset->loadTexture();

	initProjection();

	mainFrameBuffer = createFrameBuffer(0, 0, MAIN_FRAME_BUFFER_WIDTH, MAIN_FRAME_BUFFER_HEIGHT);
	hudFrameBuffer = createFrameBuffer(HUD_FRAME_BUFFER_X , HUD_FRAME_BUFFER_Y, HUD_FRAME_BUFFER_WIDTH, HUD_FRAME_BUFFER_HEIGHT);
	radarFrameBuffer = createFrameBuffer(RADAR_FRAME_BUFFER_X, RADAR_FRAME_BUFFER_Y, RADAR_FRAME_BUFFER_WIDTH, RADAR_FRAME_BUFFER_HEIGHT);

	data = configure(ModelData::quadBindable, DrawMode::TRIANGLES);
}

void Renderer::initProjection() const {
	Mat4 mainFrameBufferProjection = Projection::getOrthographicProjection(MAIN_FRAME_BUFFER_WIDTH, MAIN_FRAME_BUFFER_HEIGHT);
	Mat4 hudFrameBufferProjection = Projection::getOrthographicProjection(HUD_FRAME_BUFFER_WIDTH, HUD_FRAME_BUFFER_HEIGHT);
	Mat4 radarFrameBufferProjection = Projection::getOrthographicProjection(RADAR_FRAME_BUFFER_WIDTH, RADAR_FRAME_BUFFER_HEIGHT);

	standardShader->use();
	standardShader->setUniformMatrix4(PROJECTION, mainFrameBufferProjection);

	hudShader->use();
	hudShader->setUniformMatrix4(PROJECTION, hudFrameBufferProjection);

	backgroundShader->use();
	backgroundShader->setUniformMatrix4(PROJECTION, mainFrameBufferProjection);

	radarShader->use();
	radarShader->setUniformMatrix4(PROJECTION, radarFrameBufferProjection);
}

void Renderer::render() const {
	//glEnable(GL_POLYGON_MODE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	renderBackground();
	renderEntites();
	renderHUD();
	renderRadar();

	//glDisable(GL_POLYGON_MODE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Switch to this shader in order to render
	// everthing as a simple flipped texture on a quad
	framebufferShader->use();
}

void Renderer::renderBackground() const {
	background->bind();
	bindFrameBuffer(mainFrameBuffer);

	Vec2 scale = Vec2(MAIN_FRAME_BUFFER_WIDTH, WIN_HEIGHT);
	Mat4 transformation = Mat4::getTransformation(Vec2(), scale);
	prepareBackgroundShader({ transformation, TextureAtlas::Background::RECT });

	draw(data);
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

	Label l = Label(to_string(game->getScore()), 0, WIN_HEIGHT - 95);
	for (RenderUnit u : l.getRenderUnits()) {
		prepareHUDShader(u);
		draw(data);
	}

	Vec2 roundLabelPosition = Vec2(0, 50);
	prepareHUDShader({ Mat4::getTransformation(roundLabelPosition, Vec2(100, 20)), TextureAtlas::Font::ROUND });
	draw(data);

	Vec2 roundPosition = Vec2(180, 50);
	prepareHUDShader({ Mat4::getTransformation(roundPosition, Vec2(20, 20)), TextureAtlas::Font::ONE });
	draw(data);
}

void Renderer::renderRadar() const {
	bindFrameBuffer(radarFrameBuffer);

	prepareRadarShader({ Mat4::getTransformation(Vec2(0, 0), Vec2(RADAR_FRAME_BUFFER_WIDTH, RADAR_FRAME_BUFFER_HEIGHT)) }, RADAR_BACKGROUND_COLOR);
	draw(data);

	Vec2 playerPosition = game->getPlayerPosition();
	vector<Vec2> stationPositions = game->getStationPositions();

	float RH = RADAR_FRAME_BUFFER_HEIGHT;
	float WH = WORLD_HEIGHT;

	float ratioX = (float)RADAR_FRAME_BUFFER_WIDTH / (float)WORLD_WIDTH;
	float ratioY = RH / WH;

	Vec2 ratio = Vec2(ratioX, ratioY);

	for (Vec2 position : game->getStationPositions()) {
		prepareRadarShader({ Mat4::getTransformation(position * ratio, Vec2(10, 10)) }, RADAR_STATION_COLOR);
		draw(data);
	}
	

	if (playerPosition.x < 0 && playerPosition.y < 0)
		return;

	prepareRadarShader({ Mat4::getTransformation(playerPosition * ratio, Vec2(10, 10)) }, RADAR_PLAYER_COLOR);
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

void Renderer::prepareRadarShader(const RenderUnit unit, const Color color) const {
	radarShader->use();
	radarShader->setUniformMatrix4(TRANSFORM, unit.transformation);
	radarShader->setColor(COLOR, color);
}

void Renderer::prepareBackgroundShader(const RenderUnit unit) const {
	Mat3 textureTransformation = getTextureCoordinates(unit.textureTransform);

	backgroundShader->use();
	backgroundShader->setUniformMatrix4(TRANSFORM, unit.transformation);
	backgroundShader->setUniformMatrix3(TEXTURE_TRANSFORM, textureTransformation);
	backgroundShader->setUniformMatrix4(VIEW, game->getCameraTransformation());
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