#include "game.hpp"


int game::getround(){return round;}

bool game::roundhasended(int roundnum)
{
    int endround = getround() + roundnum;
    if (endround == getround())
    {
        return true;
    }
    return false;
}

void game::choosehero() {
    cout << "player1 choose your hero\n"; //من نخوندم سند رو کامل که باید متن ها چی باشه دقیقا یا پلیر ها بلاید اسم داشته باشن یا نه خودت اینجاهارو چک کن
    player1.addhero();
    cout << "";
    player2.addhero();
}

void game::playround(){
    cout <<"----Round----"<< round << endl;
    hero* h1 = player1.getheroes();
    hero* h2 = player2.getheroes();

    if (h1 && h2) {
        cout << "player1 attacks!\n";
        h1->ability1(*h2);

        if (h2->isAlive()) {
            cout << "player2 attacks!\n";
            h2->ability1(*h1);
        }
    }
}

void game::winner() {
    if (!player1.hasALive()) {
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

    while(!isover) {
        playround();
        winner();
        round++;
    }

    cout << "----game over----\n";
}