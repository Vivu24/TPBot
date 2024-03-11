#pragma once

#include "MissilesFacade.h"

class Vector2D;
class RandomNumberGenerator;

class MissilesUtils :
    public MissilesFacade
{
public:
    MissilesUtils();
    virtual ~MissilesUtils();

    void remove_all_missiles() override;
    void create_missiles() override;

private:
    RandomNumberGenerator& rand_;
};

