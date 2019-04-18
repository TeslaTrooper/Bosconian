#ifndef RENDERER
#define RENDERER

#include <BaseOpenGLRenderer.h>

#include "Game.h"

class Renderer : public BaseOpenGLRenderer {

	Game* const game;

	void render() const override;
	void setup() override;

public:
	
	Renderer(Game* const game) : game(game) {};
	~Renderer();
};

#endif RENDERER