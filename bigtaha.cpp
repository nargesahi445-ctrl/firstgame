#include "bigtaha.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

Btaha::Btaha() : hero("big taha", 500, 4) {}

void Btaha::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;
    
    vector<hero*> enemies = enemyteam.getheroes();
    for (auto enemyh : enemies) {
        if (enemyh != nullptr && enemyh->isAlive()) {
            enemyh->takeGroupDamage(30);
        }
    }
    myteam.decrease_energy(3);
}

void Btaha::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    if (!enemyTarget.isAlive()) {
        cout << "Target is dead!" << endl;
        return;
    }
    
    enemyTarget.takeDamage(90);
    
    this->setHidden(true);
    this->setTargetRound(currentGame.getround() + 1);
    
    cout << this->getName() << " is now hidden!" << endl;
    myteam.decrease_energy(4);
}

void Btaha::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 3) return;
    if (!canusespecial()) return;
    
    int currentround = currentGame.getround();

    if (this->bombTarget != nullptr && currentround >= this->bombActivationRound) {
        cout << "\"این یکی برای داداش کوچیکم بود... حالا نوبت تونه...\"" << endl;
        
    if (this->bombTarget->isAlive()) {
        int enemyHP = this->bombTarget->getHP();
        if (enemyHP <= 360) {
            this->bombTarget->takeDamage(enemyHP); 
            cout << this->bombTarget->getName() << " was eliminated by the bomb!" << endl;
        } else {
            this->bombTarget->takeDamage(200);
            cout << this->bombTarget->getName() << " took 200 damage from the bomb!" << endl;
        }
    }
        this->bombTarget = nullptr;
        this->bombActivationRound = -1;
        resetrage();
        myteam.decrease_energy(3);
        return;
    }

    if (currentround - this->lastUsedRound < 4) {
        cout << "Special ability cooldown: " << 4 - (currentround - this->lastUsedRound) << " rounds left" << endl;
        return;
    }

    vector<hero*> allenemies = enemyteam.getheroes();
    vector<hero*> aliveenemies;
    for (hero* enemy : allenemies) {
        if (enemy->isAlive() && !enemy->getIsHidden()) {
            aliveenemies.push_back(enemy);
        }
    }

    if (aliveenemies.empty()) {
        cout << "No alive enemies to target!" << endl;
        return;
    }

    this->lastUsedRound = currentround;
    int randomIndex = rand() % aliveenemies.size();
    this->bombTarget = aliveenemies[randomIndex];
    this->bombActivationRound = currentround + 1;
    
    cout << "\"این یکی برای داداش کوچیکم بود...\"" << endl;
    cout << "Bomb planted on " << this->bombTarget->getName() << "! Will explode next round!" << endl;
    
    resetrage();
    myteam.decrease_energy(3);
}