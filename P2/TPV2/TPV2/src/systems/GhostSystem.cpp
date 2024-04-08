#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "ImmunitySystem.h"

GhostSystem::GhostSystem() :
	lastGenerationTime(0),
	ghostGenerationTime(5000)
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
	
}

void GhostSystem::update()
{
	if (lastGenerationTime + ghostGenerationTime < sdlutils().virtualTimer().currTime() && 
		!(mngr_->getSystem<ImmunitySystem>()->getInv() || mngr_->getEntities(ecs::grp::GHOST).size() >= 10)) {

		lastGenerationTime = sdlutils().virtualTimer().currTime();

		addGhost();
	}

	for (auto &g : mngr_->getEntities(ecs::grp::GHOST)) {
		auto tf = mngr_->getComponent<Transform>(g);

		int rand = sdlutils().rand().nextInt(1, 1000);

		//randon chance para actualizar el vecto de velocidad
		if (rand < 5) {

			Vector2D posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;

			tf->vel_ = (posPM - tf->pos_).normalize() * 1.1f;
		}

		tf->pos_ = tf->pos_ + tf->vel_;

	}
}

void GhostSystem::recieve(const Message& msg)
{
	switch (msg.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		if (msg.ghost_collision_data.invulnerability)
			mngr_->setAlive(msg.ghost_collision_data.entityToDelete, false);
		break;
	case _m_IMMUNITY_START:
		setVulnerable(true);
		break;
	case _m_IMMUNITY_END:
		setVulnerable(false);
		break;
	case _m_ROUND_START:
		lastGenerationTime = sdlutils().virtualTimer().currTime();
		break;
	case _m_ROUND_OVER:
	case _m_GAME_OVER:
		deleteGhosts();
		break;
	default:
		break;
	}
}

void GhostSystem::addGhost()
{	// create the ghost entity
	//
	auto ghost = mngr_->addEntity(ecs::grp::GHOST);
	Transform* pmTR_ = mngr_->addComponent<Transform>(ghost);
	Vector2D pos;

	switch (sdlutils().rand().nextInt(0,4))
	{
	case 0:
		pos = Vector2D(0, 0);
		break;
	case 1:
		pos = Vector2D(sdlutils().width(), 0);
		break;
	case 2:
		pos = Vector2D(sdlutils().width(), sdlutils().width());
		break;
	case 3: 
		pos = Vector2D(0, sdlutils().width());
		break;
	}
	auto s = 50.0f;
	pmTR_->init(pos, Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman"),
		8, 8,
		0, 0, //
		128, 128, //
		4, 0, //
		1, 8);
}

void GhostSystem::deleteGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOST))
		mngr_->setAlive(e, false);
}

void GhostSystem::setVulnerable(bool v)
{
	switch (v)
	{
	case true:
		for (auto& e : mngr_->getEntities(ecs::grp::GHOST)) {
			mngr_->getComponent<ImageWithFrames>(e)->setImage(6, 3, 2, 1);
		}
		break;
	case false:
		for (auto& e : mngr_->getEntities(ecs::grp::GHOST)) {
			mngr_->getComponent<ImageWithFrames>(e)->setImage(0, 4, 8, 1);
		}
	default:
		break;
	}
}
