#include "CollisionSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

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
			std::cout << "col f";
		}
	}

	// Ghost Collisions

	for (int i = 0; i < ghosts.size(); i++) {
		auto gTR = mngr_->getComponent<Transform>(ghosts[i]);
		if (Collisions::collides(pmTR->getPos(), pmTR->getWidth(), pmTR->getHeight(), gTR->getPos(), gTR->getWidth(), gTR->getHeight())) {
			std::cout << "col g";
		}
	}
}
