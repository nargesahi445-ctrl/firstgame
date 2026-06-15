#pragma once
#include "team.hpp"
#include "hero.hpp"
#include "game.hpp"
#include <string>

class Btaha
{
    private:
    int targetround = -1;
    int lastUsedRound = -4;   
    hero* bombTarget = nullptr; 
    int bombActivationRound = -1;
    public :
    Btaha();
    virtual void ability1(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam);
    virtual void ability2(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam , game& , int);
    virtual void specialability(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam , game& currentGame);

};