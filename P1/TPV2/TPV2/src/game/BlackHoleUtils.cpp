#include "BlackHoleUtils.h"

#include "../components/Generations.h"
#include "../components/Image.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/Transform.h"
#include "../components/RotationComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

BlackHoleUtils::BlackHoleUtils() : rand_(sdlutils().rand()), rotation(5) {}

BlackHoleUtils::~BlackHoleUtils()
{
}

void BlackHoleUtils::create_black_hole(int n)
{
	for (int i = 0; i < n; ++i) {
		int sign = rand_.nextInt(1, 5);
		int rnd = rand_.nextInt(100, 300);

		Vector2D pos;
		switch (sign)
		{
		case 1:
			pos = Vector2D(sdlutils().width() / 2 - rnd, sdlutils().height() / 2 - rnd);
			break;
		case 2:
			pos = Vector2D(sdlutils().width() / 2 + rnd, sdlutils().height() / 2 + rnd);
			break;
		case 3:
			pos = Vector2D(sdlutils().width() / 2 - rnd, sdlutils().height() / 2 + rnd);
			break;
		case 4:
			pos = Vector2D(sdlutils().width() / 2 + rnd, sdlutils().height() / 2 - rnd);
			break;
		default:
			break;
		}

		auto mngr = Game::instance()->getMngr();

		auto a = mngr->addEntity(ecs::grp::BLACK_HOLES);

		auto g = rand_.nextInt(1, 4);

		mngr->addComponent<Transform>(a, pos, Vector2D(0, 0), 10 + 5 * g, 10 + 5 * g, 0.0f);
		//mngr->addComponent<ShowAtOpossiteSide>(a);
		//mngr->addComponent<Generations>(a, g);
		mngr->addComponent<Image>(a, &sdlutils().images().at("black-hole"));
		mngr->addComponent<RotationComponent>(a, rotation);
	}
}

void BlackHoleUtils::remove_all_black_holes()
{
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::BLACK_HOLES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}
