#include "hero.hpp"
using namespace std;

hero::hero(string name,int hp,int rager) :
    name(name) , hp(hp) , rage(0) , rager(rager) , currage(0) , maxhp(hp) {}

hero::~hero() {}

bool hero:: getIsHidden() const{return is_hidden;}

void hero::setHidden(bool status){is_hidden = status;}

void hero::takeDamage(int damage) {

    if (shield > 0) {
        if (shield <= damage) {
            sheild -= damage;
            return;
        }

        if (shield > damage) {
            damage -= shield;
            shield = 0;
        }
    }

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

void hero::addshield(int amount , int turn) {
    shield = amount;
    shieldturn = turn;    
}

void hero::updateshield() {
    if (shieldturn > 0) {
        sheildturn--;
        if (shieldturn == 0) {
            shield = 0;
        }
    }
}

