#include "game.hpp"
#include "amin.hpp"
#include "dani.hpp"
#include "bigtaha.hpp"
#include "littletaha.hpp"
#include "whitedoctor.hpp"
#include <iostream>
using namespace std;

bool game::roundhasended(int roundnum) {
    return getround() >= roundnum;
}

void game::choosehero() {
    cout << "++player1 choose your hero\n";
    // ایجاد هیرو و اضافه کردن به تیم
    aminimani* h1 = new aminimani();
    player1.addhero(h1);
    
    cout << "++player2 choose your hero\n";
    danigolang* h2 = new danigolang();
    player2.addhero(h2);
}

void game::playround() {
    cout << "----Round " << round << "----" << endl;
    
    // افزایش انرژی در هر راند
    increaseEnergyAll();
    
    // پیدا کردن اولین هیرو زنده
    hero* h1 = nullptr;
    hero* h2 = nullptr;
    hero* ally1 = nullptr;
    hero* ally2 = nullptr;
    
    // پیدا کردن هیروهای زنده برای تیم ۱
    for (auto h : player1.getheroes()) {
        if (h->isAlive()) {
            if (h1 == nullptr) h1 = h;
            else if (ally1 == nullptr) ally1 = h;
        }
    }
    if (ally1 == nullptr) ally1 = h1; // اگر تنها بود خودش رو ally قرار بده
    
    // پیدا کردن هیروهای زنده برای تیم ۲
    for (auto h : player2.getheroes()) {
        if (h->isAlive()) {
            if (h2 == nullptr) h2 = h;
            else if (ally2 == nullptr) ally2 = h;
        }
    }
    if (ally2 == nullptr) ally2 = h2;

    if (h1 && h2) {
        cout << "player1 attacks!\n";
        h1->ability1(*h2, *ally1, player2, player1);

        if (h2->isAlive()) {
            cout << "player2 attacks!\n";
            h2->ability1(*h1, *ally2, player1, player2);
        }
    }
    
    // آپدیت شیلدها
    for (auto h : player1.getheroes()) h->updateshield();
    for (auto h : player2.getheroes()) h->updateshield();
}

void game::winner() {
    if (!player1.hasAlive()) {
        cout << "Player 2 wins!\n";
        isOver = true;
    }
    else if (!player2.hasAlive()) {
        cout << "Player 1 wins!\n";
        isOver = true;
    }
}

void game::startgame() {
    cout << "----GAME START----\n";
    choosehero();

    while (!isOver) {
        playround();
        handleUnhiding(player1);
        handleUnhiding(player2);
        winner();
        round++;
    }

    cout << "----GAME OVER----\n";
}

void game::handleUnhiding(team& myteam) {
    vector<hero*>& teamheroes = myteam.getheroes();
    vector<hero*> toAdd;

    for (auto h : teamheroes) {
        if (h != nullptr && h->getIsHidden()) {
            if (h->getTargetRound() == round) {
                h->setHidden(false);
                h->setTargetRound(-1);
                toAdd.push_back(h);
                cout << h->getName() << " is now unhidden!" << endl;
            }
        }
    }
    
    // اضافه کردن هیروهای برگشته
    for (auto h : toAdd) {
        // اگر قبلاً در تیم نیست اضافه کن
        bool found = false;
        for (auto existing : teamheroes) {
            if (existing == h) {
                found = true;
                break;
            }
        }
        if (!found) {
            myteam.addhero(h);
        }
    }
}

void game::increaseEnergyAll() {
    player1.increase_energy(2);  
    player2.increase_energy(2);
}