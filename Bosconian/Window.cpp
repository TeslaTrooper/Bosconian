#include "Window.h"

Window::Window(BaseOpenGLRenderer* const renderer, Game* const game) :
	BaseOpenGLWindow(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Bosconian | OpenGL"), game(game) {
	registerKeyListener();
}

void Window::checkInput(float dt) {
	if (UserInputController::isKeyPressed(KEY_SPACE)) {
		//UserInputController::release(KEY_SPACE);
		printf("Space pressed!\n");
	}

	if (UserInputController::isKeyPressed(KEY_LEFT)) {
		UserInputController::release(KEY_LEFT);
		printf("Left pressed!\n");
		game->setShipDirection(DIRECTION_LEFT);
	}

	if (UserInputController::isKeyPressed(KEY_RIGHT)) {
		UserInputController::release(KEY_RIGHT);
		printf("Right pressed!\n");
		game->setShipDirection(DIRECTION_RIGHT);
	}

	if (UserInputController::isKeyPressed(KEY_DOWN)) {
		UserInputController::release(KEY_DOWN);
		printf("Down pressed!\n");
		game->setShipDirection(DIRECTION_DOWN);
	}

	if (UserInputController::isKeyPressed(KEY_UP)) {
		UserInputController::release(KEY_UP);
		printf("Up pressed!\n");
		game->setShipDirection(DIRECTION_UP);
	}
}