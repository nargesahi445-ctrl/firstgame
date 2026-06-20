#include "whitedoctor.hpp"
#include "game.hpp"
#include <iostream>
#include <vector>

using namespace std;

WhiteDoctor::WhiteDoctor() : hero("White Doctor", 550, 4) {}

void WhiteDoctor::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;
    
    enemyTarget.takeDamage(40);
    allyTarget.heal(40);
    myteam.decrease_energy(3);
}

void WhiteDoctor::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    dopingTarget = allyTarget.getName();
    dopingRoundsLeft = 2;
    
    cout << getName() << " uses doping on " << allyTarget.getName() << " for 2 rounds!" << endl;
    myteam.decrease_energy(4);
}

void WhiteDoctor::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    if (!canusespecial()) {
        cout << "Not enough rage for Special Ability!" << endl;
        return;
    }
    
    int currentRound = currentGame.getround();
    if (currentRound - doctorLastUsedRound < 4) {
        cout << "Special ability cooldown: " << 4 - (currentRound - doctorLastUsedRound) << " rounds left" << endl;
        return;
    }

    cout << "\"بیاریدش روی میز... زنده می‌مونه اگه شانس بیاره...\"" << endl;

    vector<hero*> teamHeroes = myteam.getheroes();
    bool revivedSomeone = false;

    for (hero* h : teamHeroes) {
        if (h != this && !h->isAlive()) {
            h->heal(200);
            cout << h->getName() << " has been revived with 200 HP!" << endl;
            revivedSomeone = true;
            break;
        }
    }

    if (revivedSomeone) {
        resetrage();
        myteam.decrease_energy(4);
        doctorLastUsedRound = currentRound;  
    } else {
        cout << "No dead ally found to revive!" << endl;
    }
}

void WhiteDoctor::updateDoping() {
    if (dopingRoundsLeft > 0) {
        dopingRoundsLeft--;
    }
}