#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

GhostSystem::GhostSystem()
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
	// create the PacMan entity
	//
	auto ghost = mngr_->addEntity(ecs::grp::GHOST);
	Transform* pmTR_ = mngr_->addComponent<Transform>(ghost);
	auto s = 50.0f;
	auto x = 0;
	auto y = 0;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman"),
		8, 8,
		0, 0, //
		128, 128, //
		4, 0, //
		1, 8);

}

void GhostSystem::update()
{
	for (auto &g : mngr_->getEntities(ecs::grp::GHOST)) {
		auto tf = mngr_->getComponent<Transform>(g);

		int rand = sdlutils().rand().nextInt(1, 1000);

		//randon chance para actualizar el vecto de velocidad
		if (rand < 5) {

			auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;

			tf->vel_ = (posPM - tf->pos_).normalize() * 1.1f;
		}

		tf->pos_ = tf->pos_ + tf->vel_;
	}
}
