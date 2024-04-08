#include "PauseState.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/messages.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"

PauseState::PauseState() : 
	msg_(&sdlutils().msgs().at("Pause"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}

PauseState::~PauseState()
{
}

void PauseState::update()
{
	if (ih().keyDownEvent()) {
		Game::instance()->setState(Game::State::RUNNING);
	}
	msg_->render(dest_);
}

void PauseState::onEnter()
{
}

void PauseState::onExit()
{
}
