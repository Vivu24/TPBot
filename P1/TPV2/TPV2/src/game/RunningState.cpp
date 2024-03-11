// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "BlackHoleFacade.h"
#include "MissilesFacade.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, BlackHoleFacade *bh_mngr, MissilesFacade *m_mngr) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr), //
		bh_mngr_(bh_mngr), //
		m_mngr_(m_mngr), //
		lastTimeGeneratedAsteroids_(), //
		lastTimeGeneratedMissile_() {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto& bh = mngr->getEntities(ecs::grp::BLACK_HOLES);
	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);

	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}
	for (auto b : bh) {
		mngr->update(b);
	}
	for (auto m : missiles) {
		mngr->update(m);
	}

	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto b : bh) {
		mngr->render(b);
	}
	for (auto m : missiles) {
		mngr->render(m);
	}
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}

	// Timer to instantiate a Missle every 15 seconds

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedMissile_ + 15000) {
		m_mngr_->create_missiles();
		lastTimeGeneratedMissile_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	lastTimeGeneratedMissile_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto &blackHoles = mngr->getEntities(ecs::grp::BLACK_HOLES);
	auto num_of_blackHoles = blackHoles.size();

	auto& missiles = mngr->getEntities(ecs::grp::MISSILES);
	auto num_of_missiles = missiles.size();

	auto num_of_asteroids = asteroids.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

		// asteroid with blackholes
		for (auto bh : blackHoles) {
			auto bhTR = mngr->getComponent<Transform>(bh);
			if (Collisions::collidesWithRotation( //
				bhTR->getPos(), //
				bhTR->getWidth(), //
				bhTR->getHeight(), //
				bhTR->getRot(),
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
				ast_mngr_->teleport_asteroid(a);
				continue;
			}
		}

		// asteroid with missiles
		for (auto m : missiles) {
			auto mTR = mngr->getComponent<Transform>(m);
			if (Collisions::collidesWithRotation( //
				mTR->getPos(), //
				mTR->getWidth(), //
				mTR->getHeight(), //
				mTR->getRot(),
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
				ast_mngr_->split_astroid(a);
				continue;
			}
		}
	}

	for (auto i = 0u; i < num_of_blackHoles; i++) {
		auto bh = blackHoles[i];
		if (!mngr->isAlive(bh))
			continue;

		// blackhole with fighter
		auto bhTR = mngr->getComponent<Transform>(bh);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			bhTR->getPos(), //
			bhTR->getWidth(), //
			bhTR->getHeight(), //
			bhTR->getRot())) {
			onFigherDeath();
			return;
		}	
	}

	for (auto i = 0u; i < num_of_missiles; i++) {
		auto m = missiles[i];
		if (!mngr->isAlive(m))
			continue;

		// missile with fighter
		auto mTR = mngr->getComponent<Transform>(m);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			mTR->getPos(), //
			mTR->getWidth(), //
			mTR->getHeight(), //
			mTR->getRot())) {
			onFigherDeath();
			return;
		}

		// missile with bullets
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
					b.pos, //
					b.width, //
					b.height, //
					b.rot, //
					mTR->getPos(), //
					mTR->getWidth(), //
					mTR->getHeight(), //
					mTR->getRot())) {
					mngr->setAlive(m, false);
					b.used = false;
					continue;
				}
			}
		}
	}
}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
