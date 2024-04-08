#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/HealthComponent.h"
#include "../components/ImageWithFrames.h"

// Constructorss
RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem() {
}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
}

//Renderiza cada entity por grupos
void RenderSystem::update() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto image = mngr_->getComponent<ImageWithFrames>(pacman);
	assert(image != nullptr);
	image->render();

	auto health = mngr_->getComponent<HealthComponent>(pacman);
	assert(health != nullptr);
	health->render();

	for (auto &g : mngr_->getEntities(ecs::grp::GHOST)) {
		auto image = mngr_->getComponent<ImageWithFrames>(g);
		assert(image != nullptr);
		image->render();
	}

	for (auto &f : mngr_->getEntities(ecs::grp::FRUIT)) {
		auto image = mngr_->getComponent<ImageWithFrames>(f);
		assert(image != nullptr);
		image->render();
	}
}

