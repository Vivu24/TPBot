#include "NewGameState.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/messages.h"
#include "../sdlutils/InputHandler.h"
#include "Game.h"
#include "../ecs/Manager.h"

NewGameState::NewGameState() :
	msg_(&sdlutils().msgs().at("PressAnyKey"))
{
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());

	// Sonido intro juego
	sdlutils().soundEffects().at("pacman_intro").play();
}

NewGameState::~NewGameState()
{
}

void NewGameState::update()
{
	if (ih().keyDownEvent()) {
		Message msg;
		msg.id = _m_NEW_GAME;
		Game::instance()->getMngr()->send(msg);
	}
	msg_->render(dest_);
}

void NewGameState::onEnter()
{
}

void NewGameState::onExit()
{
}
