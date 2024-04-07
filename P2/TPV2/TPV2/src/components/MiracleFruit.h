#pragma once
#include "../ecs/Component.h"

#include <string>


class MiracleFruit
    :public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::MIRACLEFRUIT);

    MiracleFruit();
    ~MiracleFruit();

    void update() override;

    void render() override;

    void initComponent() override;

    void resetTimer();

    void startMiracle();

    bool miracleActivated = false;

    int miracleCooldown;
    int miracleDuration;
    int initialTime;



};