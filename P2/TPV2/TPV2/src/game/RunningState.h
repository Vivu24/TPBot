#pragma once

#include "GameState.h"

class PacManSystem;
class GhostSystem;

class RunningState : public GameState
{
public:
	RunningState(PacManSystem* pc, GhostSystem* g);
	~RunningState();

	void update() override;
	void onEnter() override;
	void onExit() override;
private:
	PacManSystem* pcSystem_;
	GhostSystem* gSystem_;
};

