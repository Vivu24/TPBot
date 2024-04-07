#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/CollisionSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem* g, FoodSystem* f, CollisionSystem* c) : pcSystem_(pc), gSystem_(g), fSystem_(f), cSystem_(c) {}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	auto mngr = Game::
		instance()->getMngr();

	pcSystem_->update();
	gSystem_->update();
	fSystem_->update();
	cSystem_->update();
}

void RunningState::onEnter()
{
}

void RunningState::onExit()
{
}
