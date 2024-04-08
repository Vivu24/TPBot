// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/HealthComponent.h"

PacManSystem::PacManSystem() :
	pmTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	mngr_->addComponent<HealthComponent>(pacman, &sdlutils().images().at("heart"));
	pmTR_ = mngr_->addComponent<Transform>(pacman);
	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman"), 
		8, 8, 
		0, 0, //
		128, 128, //
		0, 0, //
		1, 4); 
}

void PacManSystem::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = pmTR_->rot_ + 90.0f;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			pmTR_->vel_ = pmTR_->vel_.rotate(90.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = pmTR_->rot_ - 90.0f;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			pmTR_->vel_ = pmTR_->vel_.rotate(-90.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			// speed
			float speed = 2.0f;

			// change the length of velocity vecto to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			pmTR_->vel_ = Vector2D(0, -speed).rotate(pmTR_->rot_);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			// speed
			float speed = 0;

			// change the length of velocity vector to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			pmTR_->vel_ = Vector2D(0, -speed).rotate(pmTR_->rot_);
		}

		sdlutils().soundEffects().at("pacman_chomp").play();
	}

	// move the pacman
	pmTR_->pos_ = pmTR_->pos_ + pmTR_->vel_;

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
	else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
}

void PacManSystem::recieve(const Message& msg)
{
	auto health = mngr_->getComponent<HealthComponent>(mngr_->getHandler(ecs::hdlr::PACMAN));
	switch (msg.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		sdlutils().soundEffects().at("pacman_death").play();
		if (health->getLifes() <= 0) {
			Message msg;
			msg.id = _m_GAME_OVER;
			mngr_->send(msg);
		}
		else if (!msg.ghost_collision_data.invulnerability) {
			health->setLifes(health->getLifes() - 1);
			Message msg;
			msg.id = _m_ROUND_OVER;
			mngr_->send(msg);
		}
		break;
	case _m_ROUND_START:
		resetPacMan();
		break;
	default:
		break;
	}
}

void PacManSystem::resetPacMan()
{
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
}
