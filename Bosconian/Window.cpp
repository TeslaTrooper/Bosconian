#include "Window.h"

Window::Window(BaseOpenGLRenderer* const renderer, Game* const game) :
	BaseOpenGLWindow(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Bosconian | OpenGL"), game(game) {
	registerKeyListener();
}

void Window::checkInput(float dt) {
	bool space = UserInputController::isKeyPressed(KEY_SPACE);
	bool left = UserInputController::isKeyPressed(KEY_LEFT);
	bool right = UserInputController::isKeyPressed(KEY_RIGHT);
	bool down = UserInputController::isKeyPressed(KEY_DOWN);
	bool up = UserInputController::isKeyPressed(KEY_UP);

	if (space)
		printf("Space pressed!\n");

	if (up)		game->setShipDirection(DIRECTION_UP);
	if (left)	game->setShipDirection(DIRECTION_LEFT);
	if (right)	game->setShipDirection(DIRECTION_RIGHT);
	if (down)	game->setShipDirection(DIRECTION_DOWN);

	if (left && up)		game->setShipDirection(DIRECTION_LEFT_UP);
	if (left && down)	game->setShipDirection(DIRECTION_LEFT_DOWN);
	if (right && up)	game->setShipDirection(DIRECTION_RIGHT_UP);
	if (right && down)	game->setShipDirection(DIRECTION_RIGHT_DOWN);
}