#include "bigtaha.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

Btaha::Btaha() : hero("big taha", 500, 4) {}

void Btaha::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;
    
    vector<hero*>& enemies = enemyteam.getheroes();
    for (auto enemyh : enemies)
    {
        if (enemyh != nullptr)
        {
            enemyh->takeDamage(30);
            myteam.decrease_energy(3);
        }
        else 
        {
            cout << "enemy does not exist" << endl;
        }
    }
    myteam.decrease_energy(3);
}

void Btaha::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;
    
    vector<hero*>& enemies = enemyteam.getheroes();
    vector<hero*>& allyteam = myteam.getheroes();

    bool found = false;
    for (auto eh : enemies) {
        if (eh->getName() == enemyTarget.getName()) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "enemy hero with this name does not exist" << endl;
        return;
    }

    enemyTarget.takeDamage(90);

    int targetround = -1;
    int currentround = mygame.getround();

    
   /* if (currentround == targetround) 
    {
        this->setHidden(false);
        allyteam.push_back(this);
        targetround = -1;
        return; 
    }*/ // *************** << we should handle unhiding in game.cpp >>************8
    if (targetround == -1)
    {
        targetround = currentround + 1;
        this -> setHidden(true);
        hiddenheroes.push_back(this);
        for (auto it = allyteam.begin(); it != allyteam.end(); ++it)
        {
            if (*it == this) 
            {
                allyteam.erase(it);
                break;     
            } 
        }
    } // need to change 

 myteam. decrease_energy(4);
}

void Btaha::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    
    int currentround = currentGame.getround();

    if (this->bombTarget != nullptr && currentround >= this->bombActivationRound) {
        if (this->bombTarget->isAlive()) {
            int enemyHP = this->bombTarget->getHP();
            if (enemyHP < 360) {
                this->bombTarget->takeDamage(enemyHP);
            } else {
                this->bombTarget->takeDamage(200);
            }
        }
        this->bombTarget = nullptr;
        this->bombActivationRound = -1;
        myteam.decrease_energy(4);
        return;
    }

    if (currentround - this->lastUsedRound < 4) {
        cout << "Special ability cooldown: " << 4 - (currentround - this->lastUsedRound) << " rounds left" << endl;
        return;
    }

    auto& allenemies = enemyteam.getheroes();
    vector<hero*> aliveenemies;
    for (hero* enemy : allenemies) {
        if (enemy->isAlive() && !enemy->getIsHidden()) {
            aliveenemies.push_back(enemy);
        }
    }

    if (aliveenemies.empty()) {
        return;
    }

    this->lastUsedRound = currentround;
    int randomIndex = rand() % aliveenemies.size();
    this->bombTarget = aliveenemies[randomIndex];
    this->bombActivationRound = currentround + 2;

    myteam.decrease_energy(4);
}