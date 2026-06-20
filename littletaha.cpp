#include "littletaha.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Ltaha::Ltaha() : hero("little taha", 500, 3) {}

void Ltaha::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 2) return;
    
    hero* lowestTarget = myteam.getlowestone();
    if (lowestTarget != nullptr) {
        lowestTarget->heal(20);
        cout << lowestTarget->getName() << " healed for 20 HP!" << endl;
    }
    
    enemyTarget.takeDamage(30);
    myteam.decrease_energy(2);
}

void Ltaha::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    healingTarget = allyTarget.getName();
    healingRoundsLeft = 2;
    
    cout << getName() << " starts healing " << allyTarget.getName() << " for 2 rounds!" << endl;
    myteam.decrease_energy(4);
}

void Ltaha::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    if (!canusespecial()) {
        cout << "Not enough rage for Special Ability!" << endl;
        return;
    }

    cout << "\"همه در جای خود! این منطقه آلوده است!\"" << endl;

    hero* lowestTarget = myteam.getlowestone();
    if (lowestTarget != nullptr) {
        lowestTarget->heal(200);
        cout << lowestTarget->getName() << " healed for 200 HP!" << endl;
    }
    
    resetrage();
    myteam.decrease_energy(4);
}

void Ltaha::updateHealing(team& myteam) {
    if (healingRoundsLeft > 0 && !healingTarget.empty()) {
        vector<hero*> heroes = myteam.getheroes();
        for (hero* h : heroes) {
            if (h->getName() == healingTarget && h->isAlive()) {
                h->heal(40);
                cout << h->getName() << " healed for 40 HP from little taha!" << endl;
                break;
            }
        }
        healingRoundsLeft--;
        if (healingRoundsLeft == 0) {
            healingTarget = "";
        }
    }
}