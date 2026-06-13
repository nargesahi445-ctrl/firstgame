#include "hero.hpp"
using namespace std;

hero::hero(string name,int hp,int rager) :
    name(name) , hp(hp) , rage(0) , rager(rager) , currage(0) {}

hero::~hero() {}

void hero::takeDamage(int damage) {
    hp -= damage;

    if (hp<0) hp = 0;
}

void hero::heal(int amount) {
    hp += amount;

    if(hp > maxhp) hp = maxhp;
}

bool hero::isAlive() const {return hp > 0;}

int hero::getHP() const {return hp;}

string hero::getName() const {return name;}

void hero::increaserage() {
    currage++;
    if (currage > rager)
        currage = rager;
}


bool hero::canusespecial() const {
    return currage >= rager;
}

void hero::resetrage() {currage = 0;}


