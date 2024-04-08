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
	void recieve(const Message& msg) override;

private: 

    void generateFruits();

    void resetTimers();

    void updateMiracleFruits();

    void destroyFruits();

	int nCol = 8;
	int nFil = 6;
};

