#ifndef RENDERER
#define RENDERER

#include <BaseOpenGLRenderer.h>
#include <ShaderFactory.h>
#include <Shader.h>
#include <Texture.h>

#include "Definitions.h"
#include "Game.h"

#define RASTER_SIZE			128

#define HUD_FRAME_BUFFER_WIDTH	200
#define MAIN_FRAME_BUFFER_WIDTH	WIN_WIDTH - HUD_FRAME_BUFFER_WIDTH

#define PROJECTION				"projection"
#define TRANSFORM				"transform"
#define TEXTURE_TRANSFORM		"textureTranslation"
#define VIEW					"view"
#define TEXTURE_ROTATION_PIVOT	"pivot"

class Renderer : public BaseOpenGLRenderer {

	Game* const game;

	Shader* standardShader;
	Shader* framebufferShader;
	Shader* hudShader;

	Texture* tileset;
	Texture* fontset;

	RenderData data;

	int mainFrameBuffer, hudFrameBuffer;

	void setup(int defaultFramebufferWidth, int defaultFramebufferHeight) override;
	void initProjection() const;
	void prepareStandardShader(const RenderUnit unit) const;
	void prepareHUDShader(const RenderUnit unit) const;
	Mat3 getTextureCoordinates(const Rectangle rect) const;
	Vec2 getTextureRotationPivot(const Rectangle rect) const;

	void render() const override;
	void renderEntites() const;
	void renderHUD() const;

public:
	
	Renderer(Game* const game) : game(game) {};
	~Renderer();

};

#endif RENDERER