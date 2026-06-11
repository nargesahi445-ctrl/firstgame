#pragma once
#include "hero.hpp"
include <string>

class WhiteDoctor : public hero
{
    public:
    WhiteDoctor();
    void ability1(hero& enemyTarget, hero& allyTarget) override;
    void ability2(hero& enemyTarget, hero& allyTarget) override;
    void specialability(hero& enemyTarget, hero& allyTarget) override;

};