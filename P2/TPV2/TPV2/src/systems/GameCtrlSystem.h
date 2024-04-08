#pragma once
#include "../ecs/System.h"
class GameCtrlSystem :
    public ecs::System
{
public:
    __SYSID_DECL__(ecs::sys::GAMECONTROLSYSTEM)

    void recieve(const Message&) override;
};

