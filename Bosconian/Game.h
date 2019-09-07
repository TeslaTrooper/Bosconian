#ifndef GAME
#define GAME

#include <InternalLogic.h>
#include "Definitions.h"

using namespace Rendering;

struct Game : public InternalLogic {

	virtual vector<RenderUnit> getRenderUnits() const = 0;

	virtual Mat4 getCameraTransformation() const = 0;

	virtual void setShipDirection(int direction) const = 0;

	virtual int getScore() const = 0;

	virtual int getRemainingLifes() = 0;

	virtual int getLevel() = 0;

	virtual void shoot() = 0;

	virtual Vec2 getPlayerPosition() const = 0;

	virtual vector<Vec2> getStationPositions() const = 0;

};

#endif GAME