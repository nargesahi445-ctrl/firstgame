#pragma once
#include "hero.hpp"
#include "team.hpp"
#include <string>

class game;

class WhiteDoctor : public hero {
    private:
        string dopingTarget = "";
        int dopingRoundsLeft = 0;
        int doctorLastUsedRound = -4;
        
    public:
        WhiteDoctor();
        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
        void updateDoping();
        string getDopingTarget() const { return dopingTarget; }
        int getDopingRoundsLeft() const { return dopingRoundsLeft; }
};