#pragma once
#include <string>
#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"

using namespace std;

class Ltaha : public hero {
    private:
        team& myTeam;
        string activeHeroName = "";
        int endRound = 0;
        
    public:
        Ltaha(team&);
        bool counting_rage(hero& target);

        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
};