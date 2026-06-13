#include<iostream>
using namespace std;

class game {
    team player1;
    team player2;
    int round = 1;
    bool isOver = false;

    public:
    int getround();
    bool roundhasended(int);
    void choosehero();
    void playround();
    void startgame();
    void winner();
};