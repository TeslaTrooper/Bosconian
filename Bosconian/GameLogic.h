#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <stdio.h>
#include <vector>

#include "Game.h"
#include "GameObject.h"

class GameLogic : public Game {

	vector<GameObject*> objects;

public:

	GameLogic() {
		objects.push_back(new GameObject(Vec2(100, 200), Vec2(50, 50)));
	};
	~GameLogic() {};

	void update(const float dt) override {
		for (int i = 0; i < objects.size(); i++)
			objects.at(i)->update(dt);
	
	};

	vector<RenderUnit> getRenderUnits() const override;

};

#endif GAME_LOGIC