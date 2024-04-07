#pragma once
#include "../ecs/System.h"

#include <utility>

class Transform;

class CollisionSystem
    :public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::COLLISIONSSYSTEM);

    CollisionSystem();

    ~CollisionSystem();

    void initSystem() override;
    void update() override;
    void recieve(const Message&) override;

private:

    void checkCollisions();
};