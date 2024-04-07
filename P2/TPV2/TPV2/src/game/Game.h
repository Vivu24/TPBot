// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../utils/Singleton.h"
#include "GameState.h"

class PacManSystem;
class RenderSystem;
class GhostSystem;
class FoodSystem;
class CollisionSystem;

class Game : public Singleton<Game>{
	friend Singleton<Game>;
	Game();
public:
	virtual ~Game();
	void init();
	void start();

	inline ecs::Manager* getMngr() { return mngr_; }

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	inline void setState(State s) {
		GameState* new_state = nullptr;
		switch (s) {
		case RUNNING:
			new_state = runing_state_;
			break;
		case PAUSED:
			new_state = paused_state_;
			break;
		case NEWGAME:
			new_state = newgame_state_;
			break;
		case NEWROUND:
			new_state = newround_state_;
			break;
		case GAMEOVER:
			new_state = gameover_state_;
			break;
		default:
			break;
		}
		current_state_->onExit();
		current_state_ = new_state;
		current_state_->onEnter();
	}
private:
	ecs::Manager *mngr_;

	PacManSystem *pacmanSys_;
	GhostSystem *ghostSys_;
	CollisionSystem* collisionSys_;
	FoodSystem* foodSys_;
	ecs::System *gameCtrlSys_;
	ecs::System *startsSys_;
	RenderSystem *renderSys_;

	GameState* current_state_;
	GameState* paused_state_;
	GameState* runing_state_;
	GameState* newgame_state_;
	GameState* newround_state_;
	GameState* gameover_state_;
};

