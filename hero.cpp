#include "hero.hpp"
using namespace std;

hero::hero(string name,int hp,int energy) :
    name(name) , hp(hp) , rage(0) , energy(energy) {}

hero::~hero() {}

void hero::takeDamage(int damage) {
    hp -= damage;

    if (hp<0) hp = 0;
}

bool hero::heal(int amount) {
    hp += amount;

    if(hp > maxhp) hp = maxhp;
}

bool hero::isAlive() const {return hp > 0;}

int hero::getHp() const {return hp;}

string hero::getName() const {return name;}

void hero::increaserage() {
    currage++;
    if (currage > rager)
        currage = reger;
}

bool hero::canusespecial() const {
    return currage >= reger;
}

void hero::resetrage() {currage = 0;}


