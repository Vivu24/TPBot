#pragma once
#include "../sdlutils/SDLUtils.h"

class GameState
{

public:
	virtual void update() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;


};