#include "RunningState.h"

#include "Game.h"
#include "../ecs/Manager.h"

#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/CollisionSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/RenderSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem* g, FoodSystem* f, CollisionSystem* c, ImmunitySystem* i, RenderSystem* r) : 
	pcSystem_(pc), 
	gSystem_(g), 
	fSystem_(f), 
	cSystem_(c), 
	iSystem_(i),
	rSystem_(r)
{}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	pcSystem_->update();
	gSystem_->update();
	fSystem_->update();
	cSystem_->update();
	iSystem_->update();
	rSystem_->update();
}

void RunningState::onEnter()
{
}

void RunningState::onExit()
{
}
