#pragma once
#include <string>
#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"

using namespace std;

class Ltaha : public hero {
    private:
        string healingTarget = "";
        int healingRoundsLeft = 0;
        
    public:
        Ltaha();
        
        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
        void updateHealing(team& myteam);
};