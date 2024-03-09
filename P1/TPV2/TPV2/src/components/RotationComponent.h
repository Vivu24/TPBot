#pragma once
#include "../ecs/Component.h"

class Transform;
class RotationComponent :
    public ecs::Component
{
public:
    RotationComponent(float rt);
    ~RotationComponent();

    void initComponent() override;
    void update() override;

private: 
    Transform *tr_;
    float rotation;
};

