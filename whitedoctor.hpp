#pragma once
#include "hero.hpp"
#include "team.hpp"
#include <string>

class WhiteDoctor : public hero
{
    team& myTeam;
    dopingduration= 0;
    public:
    WhiteDoctor(team &);
    void ability1(hero& enemyTarget, hero& allyTarget) override;
    void ability2(hero& enemyTarget, hero& allyTarget, game& currentGame , int basedamage) override;
    void specialability(hero& enemyTarget, hero& allyTarget , ) override;

};