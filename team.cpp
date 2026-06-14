#include "team.hpp"

team::team() {
    energy = 0;
}

void team::addhero(hero* h) {
    heroes.push_back(h);
}

vector<hero*>& team::getheroes() {return heroes;}

int team::get_energy() const {return energy;}

void team::set_energy(int energy) {
    this->energy = energy;
}

void team::decrease_energy(int amount) {
    energy -= amount;

    if (energy < 0)
        energy = 0;
}

bool team::hasAlive() const{
    for (auto h : heroes) {
        if (h->isAlive())
            return true;
    }
    return false;
}

hero* team::getlowestone() {
    her* lowest = nullptr;

    for (auto h : heroes) {
        if(!h->isAlive()) 
            continue;

        if (lowest == nullptr || h->getHP() < lowest->getHP()) {
            lowest = h;
        }
    }
    return lowest;
}