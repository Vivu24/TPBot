#pragma once
#include "GameState.h"

class SDL_Rect;
class Texture;

class PauseState :
	public GameState
{
public:
	PauseState();
	~PauseState();

	void update() override;
	void onEnter() override;
	void onExit() override;

private:
	Texture* msg_;
	SDL_Rect dest_;
};
