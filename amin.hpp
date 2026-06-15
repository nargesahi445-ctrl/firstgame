#pragma once
#include "hero.hpp"
#include "team.hpp"
#include <string>

using namespace std;

class aminimani : public hero {
    private:

    public:
    aminimani();
    void ability1(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam) override;
    void ability2(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam , game& , int) override;
    void specialability(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam) override;
};
