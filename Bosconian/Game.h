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

};

#endif GAME