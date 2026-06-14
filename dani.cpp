#include "dani.hpp"

danigolang::danigolang() : hero("dani golang" , 600 , 4) {};

void danigolang::ability1(hero& enemyTarget, team& enemyteam, team& myteam) {
    if (this->myteam.get_energy() < 2) return;

   if (this->lastTargetName == enemyTarget.getName())
        enemyTarget.takeDamage(32);

    enemyTarget.takeDamage(20);
    myteam.decrease_energy(2);
    this->lastTargetName = enemyTarget.getName();
}

void danigolang::ability2(hero& enemyTarget, team& enemyteam, team& myteam) {
    if (this->myteam.get_energy() < 2) return;

    enemyTarget.takeDamage(50);

    heroes* mosthp = nullptr;

    for (auto h :enemyteam.getheroes()) {
        if(!h->isAlive()) 
            continue;

        if (mosthp == nullptr || h->getHP > mosthp->getHP()) {
            mosthp = h;
        }
    }
    if (mosthp && mosthp != &enemytarget)
        mosthp.takeDamage(50);

    myteam.decrease_energy(4);
}

void danigolang::specialability(hero& enemyTarget, hero& allyTarget , team& myteam) {
    if (this->get_energy() < 4) return;

    if(!canusespecial())
        return;

    hero* ally = myteam.getlowestone();

    if(ally)
        ally->addshield(250,2);

    resetrage();
    myteam.decrease_energy(4);
}