
#include "whitedoctor.hpp"
#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

WhiteDoctor::WhiteDoctor(team&hometeam) : hero("White Doctor", 550, 4), myTeam(hometeam){};

void WhiteDoctor::ability1(hero& enemyTarget, hero& allyTarget) {
    cout << getName() << " uses asprin on " << enemyTarget.getName() << "!" << endl;
    enemyTarget.takeDamage(40);

    cout << getName() << " heals " << allyTarget.getName() << " with asprin!" << endl;
    allyTarget.heal(40);   
    myTeam.decrease_energy(3);

}

WhiteDoctor::ability2(hero& enemyTarget, hero& allyTarget , game& currentGame , basedamage) {
    cout << getName() << "uses doping " << endl;
    vector<hero*>& teamheroes = myTeam.getheroes();
    for (auto & h : teamheroes)
    {
        if (h->getName() == allyTarget.getName())
        {
            int rounddamage = basedamage * 0.2;
            dopingduration= 2;
            if (dopingduration > 0) 
            {
            enemyTarget.takeDamage(rounddamage); 
    
                if (currentGame.roundhasended(dopingduration)) 
                {
                    dopingduration = 0;
                    rounddamage = 0;
                }
                else 
                {
                    dopingduration--; 
                }
            }
            myTeam.decrease_energy(4);   
        }
        else 
        {
            cout << "hero does not exist" << endl;
        }
    }
}

void WhiteDoctor::specialability(hero& enemyTarget, hero& allyTarget) {
    if (!canusespecial()) {
        cout << "Not enough energy for Special Ability!" << endl;
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
        lastUsedRound = currentRound;
    } else {
        cout << "No dead ally found to revive!" << endl;
    }
}
