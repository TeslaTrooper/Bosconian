#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <stdio.h>

#include "Game.h"

class GameLogic : public Game {

public:

	GameLogic() {};
	~GameLogic() {
		printf("GameLogic Deleting\n");
	};

	void update(const float dt) override {

	};

};

#endif GAME_LOGIC