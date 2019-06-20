#ifndef SOUND_PLAYER
#define SOUND_PLAYER

#define SOUND_BLAST_OFF			1
#define SOUND_ALARAM_ALARAM		2
#define SOUND_CONDITION_RED		3
#define SOUND_SPY_SHIP_SIGHTED	4
#define SOUND_SHIP_SHOOT		5
#define SOUND_BIG_EXPLOSION		6
#define SOUND_SMALL_EXPLOSION	7

#include <SoundDriver.h>
#include "Definitions.h"

class SoundPlayer {

	SoundDriver soundDriver;

public:

	SoundPlayer() {
		soundDriver.load(SOUND_BLAST_OFF, SoundFiles::blastOff);
		soundDriver.load(SOUND_ALARAM_ALARAM, SoundFiles::alarmAlarm);
		soundDriver.load(SOUND_CONDITION_RED, SoundFiles::conditionRed);
		soundDriver.load(SOUND_SPY_SHIP_SIGHTED, SoundFiles::spyShipSighted);
		soundDriver.load(SOUND_SHIP_SHOOT, SoundFiles::shipShoot);
		soundDriver.load(SOUND_BIG_EXPLOSION, SoundFiles::bigExplosion);
		soundDriver.load(SOUND_SMALL_EXPLOSION, SoundFiles::smallExplosion);
	};

	void update(float dt) {};

	void playBlastOff() const { soundDriver.play(SOUND_BLAST_OFF, PLAY_MODE_ONCE, false); };
	void playAlarm() const { soundDriver.play(SOUND_ALARAM_ALARAM, PLAY_MODE_ONCE, false); };
	void playConditionRed() const { soundDriver.play(SOUND_CONDITION_RED, PLAY_MODE_ONCE, false); };
	void playSpyShipSighted() const { soundDriver.play(SOUND_SPY_SHIP_SIGHTED, PLAY_MODE_ONCE, false); };
	void playShipShoot() const { soundDriver.play(SOUND_SHIP_SHOOT, PLAY_MODE_ONCE, true); };
	void playBigExplosion() const { soundDriver.play(SOUND_BIG_EXPLOSION, PLAY_MODE_ONCE, true); };
	void playSmallExplosion() const { soundDriver.play(SOUND_SMALL_EXPLOSION, PLAY_MODE_ONCE, true); };

};

#endif SOUND_PLAYER
