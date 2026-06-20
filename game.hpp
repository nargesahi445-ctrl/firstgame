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
<<<<<<< HEAD
        int getround();
        bool roundhasended(int roundnum);
        void choosehero();
        void playround();
        void startgame();
        void winner();
=======
    int getround();
    bool roundhasended(int);
    void choosehero();
    void playround();
    void startgame();
    void winner();
    void handleUnhiding(team& myteam);
>>>>>>> c10774bbc7eb11e9092b8acc8c5de3fb76280376
};