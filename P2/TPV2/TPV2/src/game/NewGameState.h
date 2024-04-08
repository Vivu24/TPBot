#pragma once
#include "GameState.h"

class Texture;
class SDL_Rect;

class NewGameState :
    public GameState
{
public:
	NewGameState();
	~NewGameState();

	void update() override;
	void onEnter() override;
	void onExit() override;

private:
	Texture* msg_;
	SDL_Rect dest_;
};

