#pragma once
#include "hero.hpp"
#include "team.hpp"
#include <string>

class WhiteDoctor : public hero {
    private:
        team& myTeam;
        int dopingduration = 0;
        int doctorLastUsedRound = -4;
        
    public:
        WhiteDoctor(team&);
        void ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) override;
        void ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) override;
        void specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) override;
};