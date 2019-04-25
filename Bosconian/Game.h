#ifndef GAME
#define GAME

#include <InternalLogic.h>
#include "Definitions.h"

using namespace Rendering;

struct Game : public InternalLogic {

	virtual vector<RenderUnit> getRenderUnits() const = 0;

};

#endif GAME