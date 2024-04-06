#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem* g) : pcSystem_(pc), gSystem_(g) {}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	auto mngr = Game::
		instance()->getMngr();

	pcSystem_->update();
	gSystem_->update();
}

void RunningState::onEnter()
{
}

void RunningState::onExit()
{
}
