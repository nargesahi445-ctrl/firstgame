#include "littletaha.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Ltaha::Ltaha(team& newteam) : hero("little taha", 500, 3), myTeam(newteam) {}

void Ltaha::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 2) return;
    
    hero* lowestTarget = myTeam.getlowestone();
    if (lowestTarget != nullptr) {
        lowestTarget->heal(20);
    }
    
    enemyTarget.takeDamage(40);
    myTeam.decrease_energy(2);
}

void Ltaha::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    int currentRound = currentGame.getround();
    string name = allyTarget.getName();
    
    if (activeHeroName != name) {
        activeHeroName = name;
        endRound = currentRound + 2;
    }
    
    if (currentRound < endRound) {
        allyTarget.heal(40);
    } else {
        activeHeroName = "";
        endRound = 0;
        myTeam.decrease_energy(4);
    }
}

void Ltaha::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    
    if (!canusespecial()) {
        cout << "Not enough rage for Special Ability!" << endl;
        return;
    }

    hero* lowestTarget = myTeam.getlowestone();
    if (lowestTarget != nullptr) {
        lowestTarget->heal(200);
    }
    
    resetrage();
    myTeam.decrease_energy(4);
}

bool Ltaha::counting_rage(hero& target) {
    if (!target.canusespecial()) {
        target.increaserage();
        return false;
    }
    target.resetrage();
    return true;
}