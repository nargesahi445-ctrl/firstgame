#include<iostream>
using namespace std;

class game {
    team player1;
    team player2;

    int round = 1;

    bool isOver = false;

    public:
    void choosehero();
    void playround();
    void startgame();
    void winner();
};