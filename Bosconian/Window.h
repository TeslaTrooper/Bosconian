#ifndef WINDOW
#define WINDOW

#include <BaseOpenGLWindow.h>
#include <BaseOpenGLRenderer.h>
#include <UserInputController.h>

#include "Definitions.h"
#include "Game.h"

class Window : public BaseOpenGLWindow {

	Game* const game;

public:

	Window(BaseOpenGLRenderer* const renderer, Game* const game);

	void checkInput(float dt) override;

};

#endif WINDOW