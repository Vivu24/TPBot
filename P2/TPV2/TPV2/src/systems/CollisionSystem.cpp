#include "CollisionSystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"
#include "../systems/ImmunitySystem.h"
#include "../components/MiracleFruit.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::initSystem()
{
}

void CollisionSystem::update()
{
	checkCollisions();
}

void CollisionSystem::recieve(const Message&)
{
}

void CollisionSystem::checkCollisions()
{
	auto pacMan = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pmTR = mngr_->getComponent<Transform>(pacMan);
	auto fruits = mngr_->getEntities(ecs::grp::FRUIT);
	auto ghosts = mngr_->getEntities(ecs::grp::GHOST);
	// Fruits Collisions

	for (int i = 0; i < fruits.size(); i++) {
		auto fTR = mngr_->getComponent<Transform>(fruits[i]);
		if (Collisions::collides(pmTR->getPos(), pmTR->getWidth(), pmTR->getHeight(), fTR->getPos(), fTR->getWidth(), fTR->getHeight())) {
			//std::cout << "col f";

			sdlutils().soundEffects().at("pacman_eat").play();
			Message msg;
			msg.id = _m_PACMAN_FOOD_COLLISION;
			if(mngr_->getComponent<MiracleFruit>(fruits[i]) != nullptr)
				msg.fruit_collision_data.isMilagrosa = mngr_->getComponent<MiracleFruit>(fruits[i])->isMiracle();
			msg.fruit_collision_data.fruitToDelete = fruits[i];
			//tododododo
			mngr_->send(msg);
		}
	}

	// Ghost Collisions

	for (int i = 0; i < ghosts.size(); i++) {
		auto gTR = mngr_->getComponent<Transform>(ghosts[i]);
		if (Collisions::collides(pmTR->getPos(), pmTR->getWidth(), pmTR->getHeight(), gTR->getPos(), gTR->getWidth(), gTR->getHeight())) {
			//std::cout << "col g";

			Message msg;
			msg.id = _m_PACMAN_GHOST_COLLISION;
			msg.ghost_collision_data.invulnerability = mngr_->getSystem<ImmunitySystem>()->getInv();
			msg.ghost_collision_data.entityToDelete = ghosts[i];
			mngr_->send(msg);
		}
	}
}
