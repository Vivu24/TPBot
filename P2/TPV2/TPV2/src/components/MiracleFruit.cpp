#include "MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "ImageWithFrames.h"


MiracleFruit::MiracleFruit() :
	miracleActivated_(false),
	miracleCooldown_(sdlutils().rand().nextInt(10000, 20000)),
	miracleDuration_(),
	initialTime_(sdlutils().virtualTimer().currTime()),
	image_()
{
}

MiracleFruit::~MiracleFruit()
{
}

void MiracleFruit::update()
{
	Uint32 currentTime = sdlutils().virtualTimer().currTime();
	if (miracleActivated_) {
		if (currentTime >= initialTime_ + miracleDuration_) {
			resetTimer();
		}
	}
	else {
		if (currentTime >= initialTime_ + miracleCooldown_) {
			startMiracle();
		}
	}
}

void MiracleFruit::render()
{
}

void MiracleFruit::initComponent()
{
	image_ = mngr_->getComponent<ImageWithFrames>(ent_);

	assert(image_ != nullptr);
}

void MiracleFruit::resetTimer()
{
	initialTime_ = sdlutils().virtualTimer().currTime();
	miracleActivated_ = false;
	image_->setImage(4, 1, 1, 1);
}

void MiracleFruit::startMiracle()
{
	initialTime_ = sdlutils().virtualTimer().currTime();
	miracleDuration_ = sdlutils().rand().nextInt(1000, 5000);
	miracleActivated_ = true;
	image_->setImage(7, 1, 1, 1);
}