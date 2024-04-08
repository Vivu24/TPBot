#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/MiracleFruit.h"
#include "../game/Game.h"
#include "../components/ImageWithFrames.h"
//#include "../ecs/messages.h"

FoodSystem::FoodSystem()
{	
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
	std::cout << "food";
	generateFruits();
}

void FoodSystem::update()
{
	updateMiracleFruits();
}

void FoodSystem::recieve(const Message& msg)
{
	switch (msg.id) 
	{
	case _m_PACMAN_FOOD_COLLISION:
		mngr_->setAlive(msg.fruit_collision_data.fruitToDelete, false);
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

			auto tf = mngr_->addComponent<Transform>(fruit, 
				Vector2D((sdlutils().width() / nCol) * i + 35, (sdlutils().height() / nFil) * j + 35),
				Vector2D(0,0), fWidth, fHeight, 0);

			auto img = mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman"),
				8, 8,
				0, 0, //
				128, 128, //
				1, 4, //
				1, 1);


			int random = sdlutils().rand().nextInt(0, 1000);

			if (random < 100) {

				mngr_->addComponent<MiracleFruit>(fruit);

			}
		}
	}
}

void FoodSystem::resetTimers()
{
	for (auto& e : mngr_->getEntities(ecs::grp::FRUIT)) {

		auto miracleCmp = mngr_->getComponent<MiracleFruit>(e);
		auto img = mngr_->getComponent<ImageWithFrames>(e);

		if (miracleCmp != nullptr) {

			miracleCmp->resetTimer();
			// Sprite Normal

		}


	}
}

void FoodSystem::updateMiracleFruits()
{
	for (auto& e : mngr_->getEntities(ecs::grp::FRUIT)) {

		auto miracleCmp = mngr_->getComponent<MiracleFruit>(e);
		auto img = mngr_->getComponent<Image>(e);

		if (miracleCmp != nullptr) {


			if (miracleCmp->miracleActivated) {
				if (miracleCmp->initialTime + miracleCmp->miracleDuration < sdlutils().virtualTimer().currTime()) {
					miracleCmp->resetTimer();
					// Añadir Imagen fruta normal;
				}
			}
			else {

				if (miracleCmp->initialTime + miracleCmp->miracleCooldown < sdlutils().virtualTimer().currTime()) {
					miracleCmp->startMiracle();
					// Añadir Imagen fruta miracle

				}
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