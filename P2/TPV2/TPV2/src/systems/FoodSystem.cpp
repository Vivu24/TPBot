#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/MiracleFruit.h"
#include "../game/Game.h"
#include "../components/ImageWithFrames.h"
#include "ImmunitySystem.h"

FoodSystem::FoodSystem()
{	
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
}

void FoodSystem::update()
{
	std::vector<ecs::entity_t> fruits = mngr_->getEntities(ecs::grp::FRUIT);

	if (fruits.size() <= 0) {
		Message msg;
		msg.id = _m_GAME_OVER;
		mngr_->send(msg);

		// Sonido victoria
		sdlutils().soundEffects().at("pacman_won").play();
	}

	for (auto& e : fruits) {
		if (mngr_->hasComponent<MiracleFruit>(e)) {
			auto miracle = mngr_->getComponent<MiracleFruit>(e);
			assert(miracle != nullptr);
			miracle->update();
		}
	}
}

void FoodSystem::recieve(const Message& msg)
{
	switch (msg.id) 
	{
	case _m_PACMAN_FOOD_COLLISION:
		mngr_->setAlive(msg.fruit_collision_data.fruitToDelete, false);

		if (msg.fruit_collision_data.isMilagrosa && !mngr_->getSystem<ImmunitySystem>()->getInv()) {
			Message msg;
			msg.id = _m_IMMUNITY_START;
			mngr_->send(msg);
		}
		break;
	case _m_ROUND_START:
		for (auto& e : mngr_->getEntities(ecs::grp::FRUIT)) {
			if (mngr_->hasComponent<MiracleFruit>(e)) {
				auto miracle = mngr_->getComponent<MiracleFruit>(e);
				assert(miracle != nullptr);
				miracle->resetTimer();
			}
		}
		break;
	case _m_GAME_OVER:
		destroyFruits();
		break;
	case _m_NEW_GAME:
		generateFruits();
		break;
	default:
		break;
	}
}

void FoodSystem::generateFruits()
{
	float offsetX;
	float offsetY;

	int fWidth = 25;
	int fHeight = 25;

	int n = nCol * nFil;

	for (int i = 0; i < nCol; i++) {
		for (int j = 0; j < nFil; j++) {
			auto fruit = mngr_->addEntity(ecs::grp::FRUIT);

			mngr_->addComponent<Transform>(fruit, 
				Vector2D((sdlutils().width() / nCol) * i + 35, (sdlutils().height() / nFil) * j + 35),
				Vector2D(0,0), fWidth, fHeight, 0);

			mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman"),
				8, 8,
				0, 0, //
				128, 128, //
				1, 4, //
				1, 1);


			int random = sdlutils().rand().nextInt(0, 1000);

			if (random <= 100) {
				mngr_->addComponent<MiracleFruit>(fruit);
			}
		}
	}
}

void FoodSystem::destroyFruits()
{
	for (auto& e : mngr_->getEntities(ecs::grp::FRUIT)) {
		mngr_->setAlive(e, false);
	}
}