#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "../game/Container.h"

void
FighterCtrl::handleInput(Container* o) {
	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDLK_RIGHT)) {
			o->setRotation(5.0f);
		}
		else if (ihdlr.isKeyDown(SDLK_LEFT)) {
			o->setRotation(-5.0f);
		}
	}
}