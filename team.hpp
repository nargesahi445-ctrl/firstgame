#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include "hero.hpp"
using namespace std;

class team {
    private:
        vector<unique_ptr<hero>> heroes;
        int energy;

    public:
        team();
        void addhero(hero* h);
        vector<hero*> getheroes() const;
        int get_energy() const;
        void set_energy(int energy);
        void decrease_energy(int amount);
        void increase_energy(int amount);
        bool hasAlive() const;
        hero* getlowestone();
        int countAlive() const;
        void resetUsedFlags();
};