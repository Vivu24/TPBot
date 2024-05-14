#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"

class ImageWithFrames;

class MiracleFruit
    :public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::MIRACLEFRUIT)

    MiracleFruit();
    ~MiracleFruit();

    void update() override;

    void render() override;

    void initComponent() override;

    bool isMiracle() { return miracleActivated_; }

    void resetTimer();

private:
    void startMiracle();

    bool miracleActivated_;

    Uint32 miracleCooldown_;
    Uint32 miracleDuration_;
    Uint32 initialTime_;

    ImageWithFrames* image_;

};