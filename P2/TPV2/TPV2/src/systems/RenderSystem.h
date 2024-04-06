#pragma once
#include "../ecs/System.h"

class ImageWithFrames;

class RenderSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::RENDERSYSTEM)
	// Constructor
	RenderSystem();
	virtual ~RenderSystem();

	// Inicializar el sistema, etc.
	void initSystem() override;
	void update() override;
};
