#pragma once
#include "GameState.h"

class SDL_Rect;
class Texture;

class NewRoundState :
    public GameState
{
public:
	NewRoundState();
	~NewRoundState();

	void update() override;
	void onEnter() override;
	void onExit() override;

private:
	Texture *msg_;
	SDL_Rect dest_;
};
