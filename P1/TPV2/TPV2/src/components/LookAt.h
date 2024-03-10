#pragma once
#include "../ecs/Component.h"

class Transform;

class LookAt :
    public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::LOOKAT)

	LookAt();
	virtual ~LookAt();
	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
};

