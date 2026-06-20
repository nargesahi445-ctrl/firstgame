#include "team.hpp"

team::team() {
    energy = 0;
}

void team::addhero(hero* h) {
    heroes.push_back(unique_ptr<hero>(h));
}

vector<hero*> team::getheroes() const {
    vector<hero*> result;
    for (const auto& h : heroes) {
        result.push_back(h.get());
    }
    return result;
}

int team::get_energy() const {
    return energy;
}

void team::set_energy(int energy) {
    this->energy = energy;
}

void team::decrease_energy(int amount) {
    energy -= amount;
    if (energy < 0)
        energy = 0;
}

void team::increase_energy(int amount) {
    energy += amount;
}

bool team::hasAlive() const {
    for (const auto& h : heroes) {
        if (h->isAlive())
            return true;
    }
    return false;
}

int team::countAlive() const {
    int count = 0;
    for (const auto& h : heroes) {
        if (h->isAlive())
            count++;
    }
    return count;
}

hero* team::getlowestone() {
    hero* lowest = nullptr;
    for (const auto& h : heroes) {
        if (!h->isAlive())
            continue;
        if (lowest == nullptr || h->getHP() < lowest->getHP()) {
            lowest = h.get();
        }
    }
    return lowest;
}

void team::resetUsedFlags() {
    for (auto& h : heroes) {
        h->resetUsedFlag();
    }
}