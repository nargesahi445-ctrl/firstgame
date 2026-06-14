#include "littletaha.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Ltaha:: Ltaha(team& newteam):hero("little taha" , 500 , 3) , myTeam(newteam){}

void Ltaha:: ability1(hero& enemyTarget, hero& allyTarget)
{
   hero * lowestTarget = myTeam.getlowestone();
   if (lowestTarget != nullptr)
   {
    lowestTarget -> heal(20);
   }
   else 
   {
    cout << "we don't any alive hero" << endl;
   }
   enemyTarget.takeDamage(40);
   myTeam.decrease_energy(2);
}

void Ltaha:: ability2(hero& enemyTarget, hero& allyTarget, game& currentGame , int/*basedamage*/)
{
   static string activeHeroName = "";
    static int endRound = 0;
    int currentRound = currentGame.getround();
    string name = allyTarget.getName();
    if (activeHeroName != name)
    {
        activeHeroName = name;
        endRound = currentRound + 2;
    }
    if (currentRound < endRound)
    {
        allyTarget.heal(40);
        //cout << name << " healed 40 hp in round " << currentRound << endl;
    }
    else 
    {
        myTeam.decrease_energy(4); 
        activeHeroName = "";
        endRound = 0;
    }
} // not sure about this function (managing rounds) i need to check again

void Ltaha:: specialability(hero& enemyTarget, hero& allyTarget)
{
    allyTarget.resetrage();
    if (!canusespecial()) {
        cout << "Not enough energy for Special Ability!" << endl;
        return;
    }

    do{
        hero *lowesttarget = myTeam.getlowestone();
        if (lowesttarget != nullptr)
        {
            lowesttarget -> heal(200);
        }
        else 
        {
            cout << "we don't any alive hero" << endl;
        }
        myTeam.decrease_energy(4);
    }while (counting_rage(*this));
}

bool Ltaha:: counting_rage(hero&target)
{
    if (!target.canusespecial())
    {
        target.increaserage();
        return false;
    }
    target.resetrage();
    return true;
}