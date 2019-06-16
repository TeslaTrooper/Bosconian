#ifndef GAME_STATS
#define GAME_STATS

#define SCORE_GAIN_ASTEROID				10
#define SCORE_GAIN_MINE					20
#define SCORE_GAIN_CANNON				200
#define SCORE_GAIN_STATION_PROJECTILE	70
#define SCORE_GAIN_ENEMY_TYPE_1			50
#define SCORE_GAIN_ENEMY_TYPE_2			60
#define SCORE_GAIN_ENEMY_TYPE_SPY		70
#define SCORE_GAIN_STATION				1500

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