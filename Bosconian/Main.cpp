#include "Window.h"
#include "Renderer.h"
#include "APIFactory.h"

int main(void) {
	Game* game = APIFactory::getInstance();
	BaseOpenGLRenderer* renderer = new Renderer(game);

	BaseOpenGLWindow* window = new Window(renderer, game);
	window->run();

	delete window;

	return 0;
}