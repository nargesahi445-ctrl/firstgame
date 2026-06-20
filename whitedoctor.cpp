#include "whitedoctor.hpp"
#include <iostream>
#include <vector>

using namespace std;

WhiteDoctor::WhiteDoctor(team& hometeam) : hero("White Doctor", 550, 4), myTeam(hometeam) {}

void WhiteDoctor::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;
    
    cout << getName() << " uses asprin on " << enemyTarget.getName() << "!" << endl;
    enemyTarget.takeDamage(40);

    cout << getName() << " heals " << allyTarget.getName() << " with asprin!" << endl;
    allyTarget.heal(40);
    myTeam.decrease_energy(3);
}

void WhiteDoctor::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    cout << getName() << " uses doping " << endl;
    vector<hero*>& teamheroes = myTeam.getheroes();
    
    for (auto& h : teamheroes) {
        if (h->getName() == allyTarget.getName()) {
            int rounddamage = basedamage * 0.2;
            dopingduration = 2;
            
            if (dopingduration > 0) {
                enemyTarget.takeDamage(rounddamage);
                
                if (currentGame.roundhasended(dopingduration)) {
                    dopingduration = 0;
                    rounddamage = 0;
                } else {
                    dopingduration--;
                }
            }
            myTeam.decrease_energy(4);
            return;
        }
    }
    cout << "hero does not exist" << endl;
}

void WhiteDoctor::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    
    if (!canusespecial()) {
        cout << "Not enough rage for Special Ability!" << endl;
        return;
    }

    cout << getName() << " uses Special Ability: Operation Room!" << endl;
    vector<hero*>& teamHeroes = myTeam.getheroes();
    bool revivedSomeone = false;

    for (hero* h : teamHeroes) {
        if (h != this && !h->isAlive()) {
            cout << "\n[White Doctor]: \"Bring him to the table... he'll survive if he gets lucky.\"" << endl;
            h->heal(200);
            cout << h->getName() << " has been revived with 200 HP!" << endl;
            revivedSomeone = true;
            break;
        }
    }

    if (revivedSomeone) {
        resetrage();
        myTeam.decrease_energy(4);
<<<<<<< HEAD
        lastUsedRound = currentGame.getround();
=======
        doctorLastUsedRound = currentRound;
>>>>>>> c10774bbc7eb11e9092b8acc8c5de3fb76280376
    } else {
        cout << "No dead ally found to revive!" << endl;
    }
}