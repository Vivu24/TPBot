// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Texture;
class Transform;

struct Image: public ecs::Component {

	__CMPID_DECL__(ecs::cmp::IMAGE)

	Image();

	Image(Texture* tex);

	virtual ~Image() {
	}

	void render() override;
	void initComponent() override;

	Transform* tr_;
	Texture *tex_;
};

