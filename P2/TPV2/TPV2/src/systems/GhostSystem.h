#pragma once

#include <SDL_stdinc.h>

#include "../ecs/System.h"

class GhostSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::GHOSTSYSTEM)

	GhostSystem();
	virtual ~GhostSystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message&) override;

private:
	void setVulnerable(bool);
	void deleteGhosts();
	void addGhost();

	Uint32 ghostGenerationTime;
	Uint32 lastGenerationTime;
};

