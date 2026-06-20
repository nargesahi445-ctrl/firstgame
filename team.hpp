#pragma once
#include<iostream>
#include<vector>
#include "hero.hpp"
using namespace std;

class team {
    private:
        vector<hero*> heroes;
        int energy;

    public:
        team();
        void addhero(hero* h);
        vector<hero*>& getheroes();
        int get_energy() const;
        void set_energy(int energy);
        void decrease_energy(int amount);
        void increase_energy(int amount);
        bool hasAlive() const;
        hero* getlowestone();
};