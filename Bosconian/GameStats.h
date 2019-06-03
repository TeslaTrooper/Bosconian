#ifndef GAME_STATS
#define GAME_STATS

class GameStats {

	int score, level, remainingLifes;

public:

	GameStats() : score(0), level(1), remainingLifes(3) {}

	void gain(int value) { score += value; }
	void decreaseRemainingLifes() { remainingLifes--; }

	int getScore() const { return score; }
	int getRemainingLifes() const { return remainingLifes; }
	int getLevel() const { return level; }

};

#endif GAME_STATS