#include "GameCtrlSystem.h"
#include "../game/Game.h"
#include "../ecs/Manager.h"
#include "ImmunitySystem.h"

void GameCtrlSystem::recieve(const Message& msg)
{
	switch (msg.id)
	{
	case _m_GAME_OVER:
		Game::instance()->setState(Game::State::GAMEOVER);
		break;
	case _m_ROUND_OVER:
		Game::instance()->setState(Game::State::NEWROUND);
		break;
	case _m_ROUND_START:
		Game::instance()->setState(Game::State::RUNNING);
		break;
	case _m_NEW_GAME:
		Game::instance()->setState(Game::State::NEWROUND);
		break;
	case _m_PAUSE:
		Game::instance()->setState(Game::State::PAUSED);
		break;
	case _m_IS_MIRACLE:
		if (!mngr_->getSystem<ImmunitySystem>()->getInv()) {
			Message msg;
			msg.id = _m_IMMUNITY_START;
			mngr_->send(msg);
		}
		break;
	default:
		break;
	}
}
