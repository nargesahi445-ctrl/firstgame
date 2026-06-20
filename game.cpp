#include "game.hpp"
#include "amin.hpp"
#include "dani.hpp"
#include "bigtaha.hpp"
#include "littletaha.hpp"
#include "whitedoctor.hpp"
#include "terminal.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>      
#include <chrono>      
using namespace std;

int game::getEnergyForTeam(int teamNum) const {
    int patternIndex = (round - 1) % 3;
    return (teamNum == 1) ? energyPattern1[patternIndex] : energyPattern2[patternIndex];
}

void game::chooseHeroes() {
    TerminalUI::clearScreen();
    TerminalUI::header("HERO SELECTION");
    cout << "\nEach player must select 3 heroes!\n" << endl;
    
    auto select = [&](int p) {
        TerminalUI::printLine("\nPLAYER " + to_string(p) + " - Select your heroes:", Color::LIGHT_BLUE);
        cout << "1. aminimani (HP:500, Rage:3) - Attacker" << endl;
        cout << "2. big taha (HP:500, Rage:4) - Attacker" << endl;
        cout << "3. dani golang (HP:600, Rage:4) - Defender" << endl;
        cout << "4. little taha (HP:500, Rage:3) - Healer" << endl;
        cout << "5. White Doctor (HP:550, Rage:4) - Healer" << endl;
        
        team& t = (p == 1) ? player1 : player2;
        for (int i = 0; i < 3; i++) {
            cout << "\nChoose hero " << i+1 << " (1-5): ";
            int c; cin >> c;
            hero* h = nullptr;
            switch(c) {
                case 1: h = new aminimani(); break;
                case 2: h = new Btaha(); break;
                case 3: h = new danigolang(); break;
                case 4: h = new Ltaha(); break;
                case 5: h = new WhiteDoctor(); break;
                default: h = new aminimani();
            }
            t.addhero(h);
            TerminalUI::print("[OK] ", Color::LIGHT_GREEN);
            cout << h->getName() << " added to Team " << p << "!" << endl;
        }
    };
    
    select(1);
    select(2);
    cout << "\nPress Enter to start...";
    cin.ignore();
    cin.get();
}

hero* game::selectTarget(team& enemyTeam) {
    vector<hero*> alive;
    int idx = 1;
    TerminalUI::print("\n[Target] Select target:\n", Color::LIGHT_BLUE);
    for (auto h : enemyTeam.getheroes()) {
        if (h->isAlive()) {
            cout << idx++ << ". " << h->getName() << " (HP:" << h->getHP() << ")";
            if (h->getIsHidden()) TerminalUI::print(" [HIDDEN]", Color::LIGHT_YELLOW);
            cout << endl;
            alive.push_back(h);
        }
    }
    if (alive.empty()) { TerminalUI::printLine("[ERROR] No alive heroes!", Color::LIGHT_RED); return nullptr; }
    int c; cout << "Select (1-" << alive.size() << "): "; cin >> c;
    return (c > 0 && c <= (int)alive.size()) ? alive[c-1] : nullptr;
}

hero* game::selectAlly(team& myTeam, hero* current) {
    vector<hero*> alive;
    int idx = 1;
    TerminalUI::print("\n[Ally] Select ally:\n", Color::LIGHT_BLUE);
    for (auto h : myTeam.getheroes()) {
        if (h->isAlive() && h != current) {
            cout << idx++ << ". " << h->getName() << " (HP:" << h->getHP() << ")\n";
            alive.push_back(h);
        }
    }
    if (alive.empty()) { cout << "No other allies! Selecting yourself.\n"; return current; }
    cout << idx << ". Myself\n";
    int c; cout << "Select (1-" << idx << "): "; cin >> c;
    return (c == idx) ? current : (c > 0 && c <= (int)alive.size() ? alive[c-1] : current);
}

bool game::showAbilityMenu(hero* h, team& myTeam, team& enemyTeam, game& g, int p) {
    if (!h->isAlive() || myTeam.get_energy() < 2) {
        TerminalUI::printLine("[ERROR] Not enough energy!", Color::LIGHT_RED);
        return false;
    }
    
    TerminalUI::print("\n[Action] ", Color::LIGHT_BLUE);
    cout << h->getName() << " (HP:" << h->getHP() << ")" << endl;
    cout << "1. Ability 1\n2. Ability 2\n";
    if (h->canusespecial()) {
        TerminalUI::printLine("3. SPECIAL ABILITY [READY!]", Color::LIGHT_YELLOW);
    } else {
        cout << "3. SPECIAL ABILITY (Rage: " << h->getRageCount() << "/4)\n";
    }
    cout << "4. Skip\n";
    
    int c; cout << "Choose: "; cin >> c;
    if (c == 4) return false;
    
    hero* target = selectTarget(enemyTeam);
    if (!target) return false;
    hero* ally = selectAlly(myTeam, h);
    if (!ally) return false;
    
    switch(c) {
        case 1: h->ability1(*target, *ally, enemyTeam, myTeam); break;
        case 2: h->ability2(*target, *ally, enemyTeam, myTeam, g, 50); break;
        case 3: if(h->canusespecial()) h->specialability(*target, *ally, enemyTeam, myTeam, g); break;
        default: return false;
    }
    TerminalUI::printLine("[OK] Ability executed!", Color::LIGHT_GREEN);
    return true;
}

void game::executeTurn(team& attacking, team& defending, int p) {
    attacking.set_energy(getEnergyForTeam(p));
    TerminalUI::clearScreen();
    TerminalUI::header("TEAM " + to_string(p) + " TURN");
    TerminalUI::printLine("Energy: " + to_string(attacking.get_energy()), Color::LIGHT_BLUE);
    
    while (attacking.get_energy() > 0) {
        TerminalUI::printLine("\nEnergy left: " + to_string(attacking.get_energy()), Color::LIGHT_YELLOW);
        cout << "Select hero (0 to end turn):\n";
        
        vector<hero*> alive;
        int idx = 1;
        for (auto h : attacking.getheroes()) {
            if (h->isAlive() && !h->getIsHidden()) {
                cout << idx++ << ". " << h->getName() << " (HP:" << h->getHP() << " Rage:" << h->getRageCount();
                if (h->canusespecial()) TerminalUI::print(" [READY]", Color::LIGHT_YELLOW);
                cout << ")\n";
                alive.push_back(h);
            }
        }
        if (alive.empty()) { cout << "No alive heroes!\n"; break; }
        cout << "0. End turn\n";
        
        int c; cout << "Select: "; cin >> c;
        if (c == 0) break;
        if (c < 1 || c > (int)alive.size()) continue;
        
        if (showAbilityMenu(alive[c-1], attacking, defending, *this, p)) {
            alive[c-1]->increaserage();
        }
    }
    attacking.set_energy(0);
    attacking.resetUsedFlags();
}

void game::displayStatus() const {
    TerminalUI::clearScreen();
    TerminalUI::header("ROUND " + to_string(round));
    
    TerminalUI::printLine("\nTEAM 1 (Energy: " + to_string(getEnergyForTeam(1)) + "):", Color::LIGHT_BLUE);
    for (auto h : player1.getheroes()) {
        TerminalUI::print(h->isAlive() ? "   [ALIVE] " : "   [DEAD] ", h->isAlive() ? Color::LIGHT_GREEN : Color::LIGHT_RED);
        cout << h->getName() << " (HP:" << h->getHP() << " Rage:" << h->getRageCount() << ")";
        if (h->getIsHidden()) TerminalUI::print(" [HIDDEN]", Color::LIGHT_YELLOW);
        cout << endl;
    }
    
    TerminalUI::printLine("\nTEAM 2 (Energy: " + to_string(getEnergyForTeam(2)) + "):", Color::LIGHT_RED);
    for (auto h : player2.getheroes()) {
        TerminalUI::print(h->isAlive() ? "   [ALIVE] " : "   [DEAD] ", h->isAlive() ? Color::LIGHT_GREEN : Color::LIGHT_RED);
        cout << h->getName() << " (HP:" << h->getHP() << " Rage:" << h->getRageCount() << ")";
        if (h->getIsHidden()) TerminalUI::print(" [HIDDEN]", Color::LIGHT_YELLOW);
        cout << endl;
    }
    TerminalUI::separator();
}

void game::checkWinner() {
    bool t1 = player1.hasAlive(), t2 = player2.hasAlive();
    
    TerminalUI::clearScreen();
    TerminalUI::header("GAME OVER");
    
    if (!t1 && !t2) { TerminalUI::printLine("\n[DRAW] Both teams have no alive heroes!", Color::LIGHT_YELLOW); isOver = true; }
    else if (!t2) { TerminalUI::printLine("\n[WINNER] TEAM 1 WINS!", Color::LIGHT_BLUE); isOver = true; }
    else if (!t1) { TerminalUI::printLine("\n[WINNER] TEAM 2 WINS!", Color::LIGHT_RED); isOver = true; }
    else if (round > 15) {
        int a1 = player1.countAlive(), a2 = player2.countAlive();
        if (a1 > a2) TerminalUI::printLine("\nTEAM 1 WINS! (" + to_string(a1) + " alive)", Color::LIGHT_BLUE);
        else if (a2 > a1) TerminalUI::printLine("\nTEAM 2 WINS! (" + to_string(a2) + " alive)", Color::LIGHT_RED);
        else TerminalUI::printLine("\nDRAW! (" + to_string(a1) + " alive each)", Color::LIGHT_YELLOW);
        isOver = true;
    }
}

void game::playRound() {
    displayStatus();
    
    if (!firstTurnSet) {
        firstTeam = (rand() % 2) + 1;
        firstTurnSet = true;
        TerminalUI::printLine("\n[Random] Team " + to_string(firstTeam) + " goes first!", Color::LIGHT_YELLOW);

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    if (firstTeam == 1) {
        executeTurn(player1, player2, 1);
        if (!isOver) executeTurn(player2, player1, 2);
    } else {
        executeTurn(player2, player1, 2);
        if (!isOver) executeTurn(player1, player2, 1);
    }
    
    for (auto h : player1.getheroes()) h->updateshield();
    for (auto h : player2.getheroes()) h->updateshield();
    
    for (auto h : player1.getheroes()) {
        if (h->getIsHidden() && h->getTargetRound() == round) {
            h->setHidden(false);
            h->setTargetRound(-1);
        }
    }
    for (auto h : player2.getheroes()) {
        if (h->getIsHidden() && h->getTargetRound() == round) {
            h->setHidden(false);
            h->setTargetRound(-1);
        }
    }
    
    for (auto h : player1.getheroes()) {
        if (auto* w = dynamic_cast<WhiteDoctor*>(h)) w->updateDoping();
        if (auto* l = dynamic_cast<Ltaha*>(h)) l->updateHealing(player1);
    }
    for (auto h : player2.getheroes()) {
        if (auto* w = dynamic_cast<WhiteDoctor*>(h)) w->updateDoping();
        if (auto* l = dynamic_cast<Ltaha*>(h)) l->updateHealing(player2);
    }
    
    checkWinner();
    round++;
    if (!isOver) { cout << "\nPress Enter for next round..."; cin.ignore(); cin.get(); }
}

void game::startGame() {
    srand(time(nullptr));
    TerminalUI::clearScreen();
    TerminalUI::header("HERO BATTLE GAME");
    TerminalUI::printLine("Welcome to the Hero Battle Game!", Color::LIGHT_YELLOW);
    TerminalUI::printLine("Each team selects 3 heroes and they fight!", Color::LIGHT_BLUE);
    TerminalUI::printLine("Max 15 rounds per game.\n", Color::LIGHT_GREEN);
    cout << "Press Enter to start...";
    cin.get();
    
    chooseHeroes();
    while (!isOver) playRound();
}