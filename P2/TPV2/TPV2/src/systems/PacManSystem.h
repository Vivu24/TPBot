#pragma once
#include "../ecs/System.h"

class Transform;
class ImageWithFrames;

class PacManSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::PACMANSYSTEM)

	PacManSystem();
	virtual ~PacManSystem();

	void initSystem() override;
	void update() override;
	void recieve(const Message&) override;

private:
	void resetPacMan();

	Transform* pmTR_;
};
