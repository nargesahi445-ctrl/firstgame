#pragma once
#include <string>
#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"
using namespace std;

class Ltaha :public hero
{   team&myTeam;
    public :
    Ltaha(team&);
    bool counting_rage(hero&);
    void ability1(hero& enemyTarget, hero& allyTarget)override;
    void ability2(hero& enemyTarget, hero& allyTarget , game& , int)override;
    void specialability(hero& enemyTarget, hero& allyTarget)override;
};
