#include "MissilesUtils.h"
#include "../components/Generations.h"
#include "../components/Image.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/LookAt.h"
#include "Game.h"

MissilesUtils::MissilesUtils() : rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height()) {};

MissilesUtils::~MissilesUtils() {};

void MissilesUtils::create_missiles() {
	int rnd = rand_.nextInt(0, 4);
	Vector2D pos;

	switch (rnd)
	{
	case 0 :
		pos = Vector2D(0, 0);
		break;
	case 1:
		pos = Vector2D(sdlutils().width(), 0);
		break;
	case 2: 
		pos = Vector2D(sdlutils().width(), sdlutils().height());
		break;
	case 3:
		pos = Vector2D(0, sdlutils().height());
		break;
	default:
		break;
	}

	auto mngr = Game::instance()->getMngr();

	auto a = mngr->addEntity(ecs::grp::MISSILES);

	auto v = rand_.nextInt(1, 4);

	mngr->addComponent<Transform>(a, pos, Vector2D(v, 0), 50, 50, 0.0f);
	mngr->addComponent<Image>(a, &sdlutils().images().at("missile"));
	mngr->addComponent<LookAt>(a);
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	mngr->addComponent<Follow>(a, fighterTR->getPos());
}

void MissilesUtils::remove_all_missiles() {
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}