#include "MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"


MiracleFruit::MiracleFruit()
{
	miracleCooldown = sdlutils().rand().nextInt(10000, 20000);

	resetTimer();
}

MiracleFruit::~MiracleFruit()
{
}

void MiracleFruit::update()
{
}

void MiracleFruit::render()
{
}

void MiracleFruit::initComponent()
{
}

void MiracleFruit::resetTimer()
{
	initialTime = sdlutils().virtualTimer().currTime();
	miracleActivated = false;
}

void MiracleFruit::startMiracle()
{
	initialTime = sdlutils().virtualTimer().currTime();
	miracleDuration = sdlutils().rand().nextInt(1000, 5000);
	miracleActivated = true;

}