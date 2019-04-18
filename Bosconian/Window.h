#ifndef WINDOW
#define WINDOW

#include <BaseOpenGLWindow.h>
#include <BaseOpenGLRenderer.h>

#include "Game.h"

#define WIN_POS_X	50
#define WIN_POS_Y	100
#define WIN_WIDTH	900
#define WIN_HEIGHT	600

class Window : public BaseOpenGLWindow {

	BaseOpenGLRenderer* renderer;
	Game* game;

public:

	Window(BaseOpenGLRenderer* const renderer, Game* const game) :
		BaseOpenGLWindow(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Bosconian | OpenGL"), 
		game(game), renderer(renderer) {};

	void checkInput(float dt) override;

};

#endif WINDOW
