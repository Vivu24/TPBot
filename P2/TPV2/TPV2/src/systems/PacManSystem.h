#pragma once
#include "../ecs/System.h"
#include "../ecs/ecs.h"

class PacManSystem : public ecs::System
{
public:
	constexpr static ecs::sysId_t id = ecs::sys::PACMANSYSTEM;

	virtual ~PacManSystem(){}
	virtual void update() {

	}
};
