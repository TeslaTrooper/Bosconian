#ifndef GAME_STATS
#define GAME_STATS

class GameStats {

	int score, level, remainingLifes;

public:

	GameStats() : score(0), level(1), remainingLifes(3) {}

	void gain(int value) { score += value; }
	void decreaseRemainingLifes() { remainingLifes--; }

	int getScore() const { return score; }

};

#endif GAME_STATS