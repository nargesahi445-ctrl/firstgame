#pragma once
#include "team.hpp"
#include <iostream>
using namespace std;

class game {
    private:
        team player1;
        team player2;
        int round = 1;
        bool isOver = false;

    public:
        int getround() { return round; }
        bool roundhasended(int roundnum);
        void choosehero();
        void playround();
        void startgame();
        void winner();
        void handleUnhiding(team& myteam);
        void increaseEnergyAll();
};