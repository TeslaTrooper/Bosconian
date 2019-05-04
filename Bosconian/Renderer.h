#ifndef RENDERER
#define RENDERER

#include <BaseOpenGLRenderer.h>
#include <ShaderFactory.h>
#include <Shader.h>
#include <Texture.h>

#include "Definitions.h"
#include "Game.h"

#define RASTER_SIZE			128
#define PROJECTION				"projection"
#define TRANSFORM				"transform"
#define TEXTURE_TRANSFORM		"textureTranslation"
#define VIEW					"view"
#define TEXTURE_ROTATION_PIVOT	"pivot"

class Renderer : public BaseOpenGLRenderer {

	Game* const game;

	Shader* standardShader;
	Shader* framebufferShader;
	Texture* tileset;

	RenderData data;

	void setup() override;
	void initProjection() const;
	void prepareShaders(const RenderUnit unit) const;
	Mat3 getTextureCoordinates(const Rectangle rect) const;
	Vec2 getTextureRotationPivot(const Rectangle rect) const;


	void render() const override;

public:
	
	Renderer(Game* const game) : game(game) {};
	~Renderer();

};

#endif RENDERER