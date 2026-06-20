#pragma once
#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"
#include <string>

class Btaha : public hero {
    private:
        int targetround = -1;
        int lastUsedRound = -4;
        hero* bombTarget = nullptr;
        int bombActivationRound = -1;
        
    public:
        Btaha();
        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
};