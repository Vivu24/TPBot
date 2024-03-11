#include "RotationComponent.h"
#include "../ecs/Manager.h"
#include "Transform.h"

RotationComponent::RotationComponent(float rt) : tr_(), rotation(rt) {}

RotationComponent::~RotationComponent() {
}

void RotationComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void RotationComponent::update() {
	tr_->setRot(tr_->getRot() + rotation);
}
