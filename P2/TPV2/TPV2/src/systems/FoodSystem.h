#pragma once

#include "../ecs/System.h"

class FoodSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FOODSYSTEM)

	FoodSystem();
	virtual ~FoodSystem();

	void initSystem() override;
	void update() override;
};

