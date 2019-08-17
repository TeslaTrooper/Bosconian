#include "Controller.h"

Controller::Controller(BaseRenderer* const renderer, Game* const game) :
	BaseController(game, renderer, WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "Bosconian | OpenGL"), game(game) {
	registerKeyListener();
}

void Controller::checkInput(float dt) {
	bool space = KeyCallbackHandler::isKeyPressed(KEY_SPACE);
	bool left = KeyCallbackHandler::isKeyPressed(KEY_LEFT);
	bool right = KeyCallbackHandler::isKeyPressed(KEY_RIGHT);
	bool down = KeyCallbackHandler::isKeyPressed(KEY_DOWN);
	bool up = KeyCallbackHandler::isKeyPressed(KEY_UP);

	if (space) {
		KeyCallbackHandler::release(KEY_SPACE);
 		game->shoot();
	}

	if (up)		game->setShipDirection(DIRECTION_UP);
	if (left)	game->setShipDirection(DIRECTION_LEFT);
	if (right)	game->setShipDirection(DIRECTION_RIGHT);
	if (down)	game->setShipDirection(DIRECTION_DOWN);

	if (left && up)		game->setShipDirection(DIRECTION_LEFT_UP);
	if (left && down)	game->setShipDirection(DIRECTION_LEFT_DOWN);
	if (right && up)	game->setShipDirection(DIRECTION_RIGHT_UP);
	if (right && down)	game->setShipDirection(DIRECTION_RIGHT_DOWN);
}