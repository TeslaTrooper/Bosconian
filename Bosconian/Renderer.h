#ifndef RENDERER
#define RENDERER

#include <BaseOpenGLRenderer.h>
#include <ShaderFactory.h>
#include <Shader.h>

#include "Definitions.h"
#include "Game.h"

#define PROJECTION	"projection"
#define TRANSFORM	"transform"
#define TEXTURE		"textureTranslation"

class Renderer : public BaseOpenGLRenderer {

	Game* const game;

	Shader* standardShader;
	Shader* framebufferShader;

	void setup() override;
	void initProjection() const;

	void render() const override;

public:
	
	Renderer(Game* const game) : game(game) {};
	~Renderer();

};

#endif RENDERER