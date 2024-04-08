#pragma once
#include "../ecs/Component.h"

#include <string>

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

    int miracleCooldown_;
    int miracleDuration_;
    int initialTime_;

    ImageWithFrames* image_;

};