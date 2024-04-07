#pragma once

#include "../ecs/System.h"

class GhostSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::GHOSTSYSTEM)

	GhostSystem();
	virtual ~GhostSystem();

	void initSystem() override;
	void update() override;

	void addGhost();

private:
	bool immunityActivated = false;

	int ghostGenerationTime = 5000;
	int lastGenerationTime = 0;

	bool pacManImmunity = false;
};

