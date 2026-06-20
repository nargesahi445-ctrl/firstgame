#include "game.hpp"
#include <iostream>
using namespace std;

int game::getround() {
    return round;
}

bool game::roundhasended(int roundnum) {
    int endround = getround() + roundnum;
    if (endround == getround()) {
        return true;
    }
    return false;
}

void game::choosehero() {
    cout << "++player1 \nchoose your hero\n";
    player1.addhero();
    cout << "++player2 \nchoose your hero\n";
    player2.addhero();
}

void game::playround() {
    cout << "----Round----" << round << endl;
    
    // Get first alive hero from each team
    hero* h1 = nullptr;
    hero* h2 = nullptr;
    
    for (auto h : player1.getheroes()) {
        if (h->isAlive()) {
            h1 = h;
            break;
        }
    }
    
    for (auto h : player2.getheroes()) {
        if (h->isAlive()) {
            h2 = h;
            break;
        }
    }

    if (h1 && h2) {
        cout << "player1 attacks!\n";
        // Need proper ally target - using self for simplicity
        h1->ability1(*h2, *h1, player2, player1);

        if (h2->isAlive()) {
            cout << "player2 attacks!\n";
            h2->ability1(*h1, *h2, player1, player2);
        }
    }
}

void game::winner() {
    if (!player1.hasAlive()) {
        cout << "player 2 is win\n";
        isOver = true;
    }
    else if (!player2.hasAlive()) {
        cout << "player1 is win\n";
        isOver = true;
    }
}

void game::startgame() {
    cout << "----game start----\n";
    choosehero();

    while (!isOver) {
        playround();
        winner();
        round++;
    }

    cout << "----game over----\n";
}