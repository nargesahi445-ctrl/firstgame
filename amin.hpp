#pragma once
#include "hero.hpp"
#include "team.hpp"
#include <string>

using namespace std;

class aminimani : public hero {
    public:
        aminimani();
        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
};