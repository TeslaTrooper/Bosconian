#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <stdio.h>

#include "Game.h"

class GameLogic : public Game {

public:

	GameLogic() {};
	~GameLogic() {};

	void update(const float dt) override {
		printf("Update");
	};

};

#endif GAME_LOGIC