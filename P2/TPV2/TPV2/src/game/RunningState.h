#pragma once

#include "GameState.h"

class PacManSystem;
class GhostSystem;
class FoodSystem;
class CollisionSystem;
class ImmunitySystem;
class RenderSystem;

class RunningState : public GameState
{
public:
	RunningState(PacManSystem* pc, GhostSystem* g, FoodSystem* f, CollisionSystem* c, ImmunitySystem* i, RenderSystem* r);
	~RunningState();

	void update() override;
	void onEnter() override;
	void onExit() override;
private:
	PacManSystem* pcSystem_;
	GhostSystem* gSystem_;
	FoodSystem* fSystem_;
	CollisionSystem* cSystem_;
	ImmunitySystem* iSystem_;
	RenderSystem* rSystem_;
};

