#include "NewRoundState.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

NewRoundState::NewRoundState() :
	msg_(&sdlutils().msgs().at("PressEnter"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}

NewRoundState::~NewRoundState()
{
}

void NewRoundState::update()
{
	if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
		Message msg;
		msg.id = _m_ROUND_START;
		Game::instance()->getMngr()->send(msg);
	}
	msg_->render(dest_);
}

void NewRoundState::onEnter()
{
}

void NewRoundState::onExit()
{
}
