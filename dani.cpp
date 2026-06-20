#include "dani.hpp"

danigolang::danigolang() : hero("dani golang", 600, 4) {}

void danigolang::ability1(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam) {
    if (myteam.get_energy() < 2) return;

    if (this->lastTargetName == enemyTarget.getName()) {
        enemyTarget.takeDamage(32);
    } else {
        enemyTarget.takeDamage(20);
    }
    
    myteam.decrease_energy(2);
    this->lastTargetName = enemyTarget.getName();
}

void danigolang::ability2(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame, int basedamage) {
    if (myteam.get_energy() < 4) return;

    enemyTarget.takeDamage(50);

    hero* mosthp = nullptr;
    for (auto h : enemyteam.getheroes()) {
        if (!h->isAlive()) 
            continue;
        if (mosthp == nullptr || h->getHP() > mosthp->getHP()) {
            mosthp = h;
        }
    }
    
    if (mosthp && mosthp != &enemyTarget)
        mosthp->takeDamage(50);

    myteam.decrease_energy(4);
}

void danigolang::specialability(hero& enemyTarget, hero& allyTarget, team& enemyteam, team& myteam, game& currentGame) {
    if (myteam.get_energy() < 4) return;
    if (!canusespecial()) return;

    cout << "\"هیچ‌کس از این خط رد نمی‌شه!\"" << endl;

    hero* ally = myteam.getlowestone();
    if (ally) {
        ally->addshield(250, 2);
        cout << ally->getName() << " received a 250 HP shield for 2 turns!" << endl;
    }

    resetrage();
    myteam.decrease_energy(4);
}