#include "RenderSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

#include "../components/ImageWithFrames.h"

// Constructorss
RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem() {
}

// Inicializar el sistema, etc.
void RenderSystem::initSystem() {
	/*Message m;
	m.id = _m_OFFSET_CONTEXT;
	m.offset_context.offset = offset;
	mngr_->send(m, true);*/
}

//Renderiza cada entity por grupos
void RenderSystem::update() {
	auto pacman = mngr_->getHandler(ecs::hdlr::PACMAN);

	auto image = mngr_->getComponent<ImageWithFrames>(pacman);
	image->render();

	for (auto g : mngr_->getEntities(ecs::grp::GHOST)) {
		auto image = mngr_->getComponent<ImageWithFrames>(g);
		image->render();
	}
}

