#include "hero.hpp"
#include "team.hpp"
#include "game.hpp"
using namespace std;

hero::hero(string name, int hp, int rager) :
    name(name), hp(hp), rage(0), rager(rager), currage(0), maxhp(hp) {}

hero::~hero() {}

<<<<<<< HEAD
bool hero::getIsHidden() const {
    return is_hidden;
}
=======
int hero::getTargetRound() const{return targetround;}
void hero::setTargetRound(int rounds) {targetround = rounds;}

bool hero:: getIsHidden() const{return is_hidden;}
>>>>>>> c10774bbc7eb11e9092b8acc8c5de3fb76280376

void hero::setHidden(bool status) {
    is_hidden = status;
}

void hero::takeDamage(int damage) {
<<<<<<< HEAD
=======
    if (is_hidden) { return; }
>>>>>>> c10774bbc7eb11e9092b8acc8c5de3fb76280376
    if (shield > 0) {
        if (shield >= damage) {
            shield -= damage;
            return;
        } else {
            damage -= shield;
            shield = 0;
        }
    }
    
    hp -= damage;
    if (hp < 0) hp = 0;
}

void hero::heal(int amount) {
    hp += amount;
    if (hp > maxhp) hp = maxhp;
}

bool hero::isAlive() const {
    return hp > 0;
}

int hero::getHP() const {
    return hp;
}

string hero::getName() const {
    return name;
}

void hero::increaserage() {
    currage++;
    if (currage > rager)
        currage = rager;
}

bool hero::canusespecial() const {
    return currage >= rager;
}

void hero::resetrage() {
    currage = 0;
}

void hero::addshield(int amount, int turn) {
    shield = amount;
    shieldTurn = turn;
}

void hero::updateshield() {
    if (shieldTurn > 0) {
        shieldTurn--;
        if (shieldTurn == 0) {
            shield = 0;
        }
    }
}