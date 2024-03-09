#pragma once
#include "BlackHoleFacade.h"

class Vector2D;
class RandomNumberGenerator;

class BlackHoleUtils :
    public BlackHoleFacade
{
public:
    BlackHoleUtils();
    virtual ~BlackHoleUtils();

    void create_black_hole(int n) override;
    void remove_all_black_holes() override;

private:
    RandomNumberGenerator& rand_;
    float rotation = 5;
};

