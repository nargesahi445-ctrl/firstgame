#include "bigtaha.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

Btaha::Btaha() : hero("big taha", 500, 4) {}

void Btaha::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;
    
    vector<hero*>& enemies = enemyteam.getheroes();
    for (auto enemyh : enemies) {
        if (enemyh != nullptr && enemyh->isAlive()) {
            enemyh->takeDamage(30);
        }
    }
    myteam.decrease_energy(3);
}

void Btaha::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    enemyTarget.takeDamage(90);
    myteam.decrease_energy(4);
}

void Btaha::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    
    int currentround = currentGame.getround();

    // بررسی بمب قبلی
    if (this->bombTarget != nullptr && currentround >= this->bombActivationRound) {
        if (this->bombTarget->isAlive()) {
            int enemyHP = this->bombTarget->getHP();
            if (enemyHP < 360) {
                this->bombTarget->takeDamage(enemyHP);
            } else {
                this->bombTarget->takeDamage(200);
            }
            cout << "Bomb exploded on " << this->bombTarget->getName() << "!" << endl;
        }
        this->bombTarget = nullptr;
        this->bombActivationRound = -1;
        myteam.decrease_energy(4);
        return;
    }

    // بررسی کول‌دان
    if (currentround - this->lastUsedRound < 4) {
        cout << "Special ability cooldown: " << 4 - (currentround - this->lastUsedRound) << " rounds left" << endl;
        return;
    }

    // پیدا کردن دشمنان زنده
    auto& allenemies = enemyteam.getheroes();
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

    // کار گذاشتن بمب
    this->lastUsedRound = currentround;
    int randomIndex = rand() % aliveenemies.size();
    this->bombTarget = aliveenemies[randomIndex];
    this->bombActivationRound = currentround + 2;
    
    cout << "Bomb planted on " << this->bombTarget->getName() << "! Will explode in 2 rounds!" << endl;
    myteam.decrease_energy(4);
}