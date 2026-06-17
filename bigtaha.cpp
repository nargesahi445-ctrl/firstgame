#include "bigtaha.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib>
#include <ctime>

Btaha::Btaha() : hero("big taha" , 500 , 4){}

void Btaha::ability1(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam)
{
    vector<hero*>& enemies = enemyteam.getheroes();
    for (auto enemyh : enemies)
    {
        if (enemyh != nullptr)
        {
            bool wasHidden = enemyh->getIsHidden();
            if (wasHidden) {enemyh->setHidden(false);}
            enemyh->takeDamage(30);
            if (wasHidden) {
                enemyh->setHidden(true);
            }
           
        }
        else 
        {
            cout << "enemy does not exist" << endl;
        }
    }
    myteam.decrease_energy(3);
}

void  Btaha::ability2(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam , game&mygame , int)
{
    vector<hero*>& enemies = enemyteam.getheroes();
    vector<hero*>& allyteam = myteam.getheroes();
    static vector<hero*> hiddenheroes;
    bool found = false;
    for(auto eh : enemies)
    {
        if (eh->getName() == enemyTarget.getName())
        {
            found = true;
            break;
        }
    }
    if (found == false)
    {
        cout << "enemy hero with this name does not exist" << endl;
        return;
    }
    enemyTarget.takeDamage(90);

    if (this->getTargetRound() == -1)
    {
        this->setHidden(true);
        this->setTargetRound(0);
    }
    myteam.decrease_energy(4);
}

void Btaha::specialability(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam , game& currentGame)
{
    int currentround = currentGame.getround();

if (this -> bombTarget != nullptr && currentround >= this->bombActivationRound)
{
    if (this->bombTarget->isAlive()) {
        int enemyHP = this->bombTarget->getHP();
        if (enemyHP < 360)
        {
            this->bombTarget->takeDamage(enemyHP);
        }
        else 
        {
            this->bombTarget->takeDamage(200);
        }
        myteam.decrease_energy(3);
    }
    this->bombTarget = nullptr;
    this->bombActivationRound = -1;
    return;
}

if (currentround - this->lastUsedRound < 4) {
    cout << 4 - (currentround - this->lastUsedRound) << endl;
    return;
}

auto& allenemies = enemyteam.getHeroes(); 
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
this->bombActivationRound = currentround; 

if (this->bombTarget->isAlive()) {
    int enemyHP = this->bombTarget->getHP();
    if (enemyHP < 360)
    {
        this->bombTarget->takeDamage(enemyHP);
    }
    else 
    {
        this->bombTarget->takeDamage(200);
    }
}

this->bombTarget = nullptr;
this->bombActivationRound = -1;

}
   


