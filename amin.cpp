#include "amin.hpp"

aminimani::aminimani() : hero("amin imani", 500, 3) {}

void aminimani::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 3) return;

    if (enemyTarget.getHP() <= 110) {
        enemyTarget.takeDamage(110);
    } else {
        enemyTarget.takeDamage(55);
    }
    myteam.decrease_energy(3);
}

void aminimani::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 3) return;

    allyTarget.takeDamage(25);
    this->heal(75);
    myteam.decrease_energy(3);
}

void aminimani::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;

    int i = 0;
    for (auto e : enemyteam.getheroes()) {
        if (e->isAlive() && i < 1) {
            e->takeDamage(250);
            i++;
        }
    }

    int count = 0;
    for (auto h : myteam.getheroes()) {
        if (h->isAlive() && h != this && count < 2) {
            h->takeDamage(30);
            count++;
        }
    }

    myteam.decrease_energy(4);
}