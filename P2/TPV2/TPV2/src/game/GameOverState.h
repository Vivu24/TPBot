#pragma once
#include "GameState.h"

class Texture;
class SDL_Rect;

class GameOverState :
    public GameState
{
public:
	GameOverState();
	~GameOverState();

	void update() override;
	void onEnter() override;
	void onExit() override;

private:
	Texture* msg_;
	SDL_Rect dest_;
};

