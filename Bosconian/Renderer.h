#ifndef RENDERER
#define RENDERER

#include <BaseRenderer.h>
#include <ShaderFactory.h>
#include <Shader.h>
#include <Texture.h>

#include "Definitions.h"
#include "Game.h"
#include "Label.h"

#define RASTER_SIZE			128

#define PROJECTION				"projection"
#define TRANSFORM				"transform"
#define TEXTURE_TRANSFORM		"textureTranslation"
#define VIEW					"view"
#define COLOR					"clr"

#define RADAR_BACKGROUND_COLOR	Color(0, 137, 255)
#define RADAR_PLAYER_COLOR		Color(255, 255, 255)
#define RADAR_STATION_COLOR		Color(0, 255, 75)

class Renderer : public BaseRenderer {

	Game* const game;

	Shader* standardShader;
	Shader* framebufferShader;
	Shader* hudShader;
	Shader* backgroundShader;
	Shader* radarShader;

	Texture* tileset;
	Texture* fontset;
	Texture* background;

	RenderData data;

	int mainFrameBuffer, hudFrameBuffer, radarFrameBuffer;

	void setup(int defaultFramebufferWidth, int defaultFramebufferHeight) override;
	void initProjection() const;
	void prepareStandardShader(const RenderUnit unit) const;
	void prepareHUDShader(const RenderUnit unit) const;
	void prepareBackgroundShader(const RenderUnit unit) const;
	void prepareRadarShader(const RenderUnit unit, const Color color) const;

	Mat3 getTextureCoordinates(const Rectangle rect) const;

	void render() const override;
	void renderBackground() const;
	void renderEntites() const;
	void renderHUD() const;
	void renderRadar() const;

public:
	
	Renderer(Game* const game) : game(game) {};
	~Renderer();

};

#endif RENDERER