#include "HealthComponent.h"

#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"

HealthComponent::HealthComponent(Texture* tex) :
	tex_(tex),
	scale_(0.25),
	offset_(tex_->width()* scale_),
	init_(3),
	lifes_(3)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::render()
{
	Vector2D pos;
	for (int i = 0; i < lifes_; i++) {
		pos.set(init_ + (offset_ * i), init_);

		assert(tex_ != nullptr);
		tex_->render(build_sdlrect(pos, tex_->width() * scale_, tex_->height() * scale_));
	}
}
