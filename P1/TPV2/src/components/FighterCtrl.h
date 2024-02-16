
#include "../game/InputComponent.h"

class Container;

class FighterCtrl :
	public InputComponent 
{
public:
	FighterCtrl() {};
	~FighterCtrl() {};

	void handleInput(Container* o) override;
};