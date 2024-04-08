// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/FoodSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../systems/ImmunitySystem.h"

#include "RunningState.h"
#include "NewRoundState.h"
#include "NewGameState.h"
#include "GameOverState.h"
#include "PauseState.h"

using ecs::Manager;

Game::Game() :
		mngr_(), //
		pacmanSys_(), //
		gameCtrlSys_(), //
		immunitySys_(), //
		renderSys_(), //
		collisionSys_() {

}

Game::~Game() {
	delete mngr_;
	delete runing_state_;
	delete newround_state_;
	delete newgame_state_;
	delete gameover_state_;
	delete paused_state_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();


	// add the systems
	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	ghostSys_ = mngr_->addSystem<GhostSystem>();
	foodSys_ = mngr_->addSystem<FoodSystem>();
	collisionSys_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	immunitySys_ = mngr_->addSystem<ImmunitySystem>();

	runing_state_ = new RunningState(pacmanSys_, ghostSys_, foodSys_, collisionSys_, immunitySys_, renderSys_);
	newround_state_ = new NewRoundState();
	newgame_state_ = new NewGameState();
	gameover_state_ = new GameOverState();
	paused_state_ = new PauseState();

	current_state_ = newgame_state_;
	current_state_->onEnter();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		sdlutils().clearRenderer();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		current_state_->update();

		sdlutils().presentRenderer();

		mngr_->refresh();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

