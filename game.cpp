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
#include <algorithm>
#include <set>
using namespace std;

int game::getEnergyForTeam(int teamNum) const {
    int patternIndex = (round - 1) % 3;
    return (teamNum == 1) ? energyPattern1[patternIndex] : energyPattern2[patternIndex];
}

int getValidatedInput(int min, int max, const string& prompt = "") {
    int input;
    bool valid = false;
    while (!valid) {
        if (!prompt.empty()) {
            cout << prompt;
        }
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(1000, '\n');
            TerminalUI::printLine("[ERROR] Invalid input! Please enter a number.", Color::LIGHT_RED);
            continue;
        }
        if (input >= min && input <= max) {
            valid = true;
        } else {
            TerminalUI::printLine("[ERROR] Please enter a number between " + to_string(min) + " and " + to_string(max) + ".", Color::LIGHT_RED);
        }
    }
    return input;
}

void game::chooseHeroes() {
    TerminalUI::clearScreen();
    TerminalUI::header("HERO SELECTION");
    cout << "\nEach player must select 3 heroes!\n";
    cout << "Important: Each hero can only be selected once!\n" << endl;
    
    auto select = [&](int p) {
        TerminalUI::printLine("\nPLAYER " + to_string(p) + " - Select your heroes:", Color::LIGHT_BLUE);
        cout << "1. aminimani (HP:500, Rage:3) - Attacker" << endl;
        cout << "2. big taha (HP:500, Rage:4) - Attacker" << endl;
        cout << "3. dani golang (HP:600, Rage:4) - Defender" << endl;
        cout << "4. little taha (HP:500, Rage:3) - Healer" << endl;
        cout << "5. White Doctor (HP:550, Rage:4) - Healer" << endl;
        
        team& t = (p == 1) ? player1 : player2;
        set<int> selectedHeroes;  
        
        for (int i = 0; i < 3; i++) {
            int c = 0;
            bool validInput = false;
            while (!validInput) {
                cout << "\nChoose hero " << i+1 << " (1-5): ";
                if (!(cin >> c)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    TerminalUI::printLine("[ERROR] Invalid input! Please enter a number between 1-5.", Color::LIGHT_RED);
                    continue;
                }
                if (c < 1 || c > 5) {
                    TerminalUI::printLine("[ERROR] Please enter a number between 1-5.", Color::LIGHT_RED);
                    continue;
                }
                if (selectedHeroes.find(c) != selectedHeroes.end()) {
                    TerminalUI::printLine("[ERROR] This hero has already been selected! Choose a different hero.", Color::LIGHT_RED);
                    continue;
                }
                validInput = true;
                selectedHeroes.insert(c);
            }
            
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

        cout << "\nTeam " << p << " heroes: ";
        vector<hero*> heroes = t.getheroes();
        for (size_t i = 0; i < heroes.size(); i++) {
            cout << heroes[i]->getName();
            if (i < heroes.size() - 1) cout << ", ";
        }
        cout << endl;
    };
    
    select(1);
    cout << "\n";
    select(2);
    
    cout << "\nPress Enter to start the game...";
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
    if (alive.empty()) { 
        TerminalUI::printLine("[ERROR] No alive heroes to target!", Color::LIGHT_RED); 
        return nullptr; 
    }
    
    int c = getValidatedInput(1, alive.size(), "Select (1-" + to_string(alive.size()) + "): ");
    return alive[c-1];
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
    if (alive.empty()) { 
        cout << "No other allies! Selecting yourself.\n"; 
        return current; 
    }
    cout << idx << ". Myself\n";
    
    int c = getValidatedInput(1, idx, "Select (1-" + to_string(idx) + "): ");
    return (c == idx) ? current : alive[c-1];
}

int getAbilityCost(hero* h, int abilityNum) {

    if (dynamic_cast<aminimani*>(h)) {
        if (abilityNum == 1) return 3;
        if (abilityNum == 2) return 3;
        if (abilityNum == 3) return 4;
    }
    else if (dynamic_cast<Btaha*>(h)) {
        if (abilityNum == 1) return 3;
        if (abilityNum == 2) return 4;
        if (abilityNum == 3) return 3;
    }
    else if (dynamic_cast<danigolang*>(h)) {
        if (abilityNum == 1) return 2;
        if (abilityNum == 2) return 4;
        if (abilityNum == 3) return 4;
    }
    else if (dynamic_cast<Ltaha*>(h)) {
        if (abilityNum == 1) return 2;
        if (abilityNum == 2) return 4;
        if (abilityNum == 3) return 4;
    }
    else if (dynamic_cast<WhiteDoctor*>(h)) {
        if (abilityNum == 1) return 3;
        if (abilityNum == 2) return 4;
        if (abilityNum == 3) return 4;
    }
    return 4; 
}

bool game::showAbilityMenu(hero* h, team& myTeam, team& enemyTeam, game& g, int p) {
    if (!h->isAlive()) {
        TerminalUI::printLine("[ERROR] This hero is dead!", Color::LIGHT_RED);
        return false;
    }
    
    if (h->getIsHidden()) {
        TerminalUI::printLine("[ERROR] This hero is hidden and cannot act!", Color::LIGHT_RED);
        return false;
    }
    
    int cost1 = getAbilityCost(h, 1);
    int cost2 = getAbilityCost(h, 2);
    int cost3 = getAbilityCost(h, 3);
    
    if (myTeam.get_energy() < min(cost1, min(cost2, cost3))) {
        TerminalUI::printLine("[ERROR] Not enough energy! Need at least " + 
                             to_string(min(cost1, min(cost2, cost3))) + " energy.", Color::LIGHT_RED);
        return false;
    }
    
    TerminalUI::print("\n[Action] ", Color::LIGHT_BLUE);
    cout << h->getName() << " (HP:" << h->getHP() << ")" << endl;
    cout << "1. Ability 1 (Cost: " << cost1 << " energy)" << endl;
    cout << "2. Ability 2 (Cost: " << cost2 << " energy)" << endl;
    
    if (h->canusespecial()) {
        TerminalUI::printLine("3. SPECIAL ABILITY [READY!] (Cost: " + to_string(cost3) + " energy)", Color::LIGHT_YELLOW);
    } else {
        cout << "3. SPECIAL ABILITY (Rage: " << h->getRageCount() << "/" << "4, Cost: " << cost3 << " energy)\n";
    }
    cout << "4. Skip\n";
    
    int c = getValidatedInput(1, 4, "Choose (1-4): ");
    if (c == 4) return false;

    int selectedCost = 0;
    switch(c) {
        case 1: selectedCost = cost1; break;
        case 2: selectedCost = cost2; break;
        case 3: selectedCost = cost3; break;
    }
    
    if (myTeam.get_energy() < selectedCost) {
        TerminalUI::printLine("[ERROR] Not enough energy! Need " + to_string(selectedCost) + " energy. You have " + 
                             to_string(myTeam.get_energy()) + ".", Color::LIGHT_RED);
        return false;
    }
    
    if (c == 3 && !h->canusespecial()) {
        TerminalUI::printLine("[ERROR] Special ability is not ready yet!", Color::LIGHT_RED);
        return false;
    }
    
    hero* target = selectTarget(enemyTeam);
    if (!target) return false;
    
    hero* ally = selectAlly(myTeam, h);
    if (!ally) return false;

    int energyBefore = myTeam.get_energy();
    
    switch(c) {
        case 1: 
            h->ability1(*target, *ally, enemyTeam, myTeam);
            break;
        case 2: 
            h->ability2(*target, *ally, enemyTeam, myTeam, g, 50);
            break;
        case 3: 
            if(h->canusespecial()) {
                h->specialability(*target, *ally, enemyTeam, myTeam, g);
            }
            break;
        default: 
            return false;
    }

    if (myTeam.get_energy() == energyBefore) {
        TerminalUI::printLine("[WARNING] Energy was not consumed! Ability might not have executed properly.", Color::LIGHT_YELLOW);
        return false;
    }
    
    TerminalUI::printLine("[OK] Ability executed! Energy left: " + to_string(myTeam.get_energy()), Color::LIGHT_GREEN);
    return true;
}

void game::executeTurn(team& attacking, team& defending, int p) {
    attacking.set_energy(getEnergyForTeam(p));
    TerminalUI::clearScreen();
    TerminalUI::header("TEAM " + to_string(p) + " TURN");
    TerminalUI::printLine("Energy: " + to_string(attacking.get_energy()), Color::LIGHT_BLUE);

    cout << "\n--- YOUR TEAM ---" << endl;
    for (auto h : attacking.getheroes()) {
        cout << "  " << (h->isAlive() ? "[ALIVE]" : "[DEAD]") 
             << " " << h->getName() << " (HP:" << h->getHP() << ")";
        if (h->getIsHidden()) cout << " [HIDDEN]";
        cout << endl;
    }
    
    cout << "\n--- ENEMY TEAM ---" << endl;
    for (auto h : defending.getheroes()) {
        cout << "  " << (h->isAlive() ? "[ALIVE]" : "[DEAD]") 
             << " " << h->getName() << " (HP:" << h->getHP() << ")";
        if (h->getIsHidden()) cout << " [HIDDEN]";
        cout << endl;
    }
    
    int actionsTaken = 0;
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
        if (alive.empty()) { 
            cout << "No alive heroes available!\n"; 
            break; 
        }
        cout << "0. End turn\n";
        
        int c = getValidatedInput(0, alive.size(), "Select (0-" + to_string(alive.size()) + "): ");
        if (c == 0) break;

        int energyBefore = attacking.get_energy();
        
        if (showAbilityMenu(alive[c-1], attacking, defending, *this, p)) {

            if (attacking.get_energy() < energyBefore) {
                alive[c-1]->increaserage();
                actionsTaken++;
            }
        }
        
        if (attacking.get_energy() == energyBefore && c != 0) {
            TerminalUI::printLine("[ERROR] No energy was consumed. Please try a different action.", Color::LIGHT_RED);
        }
    }
    
    TerminalUI::printLine("\nTurn ended. Total actions performed: " + to_string(actionsTaken), Color::LIGHT_GREEN);
    attacking.set_energy(0);
    attacking.resetUsedFlags();
    
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void game::displayStatus() const {
    TerminalUI::clearScreen();
    TerminalUI::header("ROUND " + to_string(round));
    
    TerminalUI::printLine("\nTEAM 1 (Energy: " + to_string(getEnergyForTeam(1)) + "):", Color::LIGHT_BLUE);
    for (auto h : player1.getheroes()) {
        TerminalUI::print(h->isAlive() ? "   [ALIVE] " : "   [DEAD] ", h->isAlive() ? Color::LIGHT_GREEN : Color::LIGHT_RED);
        cout << h->getName() << " (HP:" << h->getHP() << "/" << (h->isAlive() ? "???" : "0") << " Rage:" << h->getRageCount() << ")";
        if (h->getIsHidden()) TerminalUI::print(" [HIDDEN]", Color::LIGHT_YELLOW);
        cout << endl;
    }
    
    TerminalUI::printLine("\nTEAM 2 (Energy: " + to_string(getEnergyForTeam(2)) + "):", Color::LIGHT_RED);
    for (auto h : player2.getheroes()) {
        TerminalUI::print(h->isAlive() ? "   [ALIVE] " : "   [DEAD] ", h->isAlive() ? Color::LIGHT_GREEN : Color::LIGHT_RED);
        cout << h->getName() << " (HP:" << h->getHP() << "/" << (h->isAlive() ? "???" : "0") << " Rage:" << h->getRageCount() << ")";
        if (h->getIsHidden()) TerminalUI::print(" [HIDDEN]", Color::LIGHT_YELLOW);
        cout << endl;
    }
    TerminalUI::separator();
}

void game::checkWinner() {
    bool t1 = player1.hasAlive(), t2 = player2.hasAlive();
    
    TerminalUI::clearScreen();
    TerminalUI::header("GAME OVER");
    
    if (!t1 && !t2) { 
        TerminalUI::printLine("\n[DRAW] Both teams have no alive heroes!", Color::LIGHT_YELLOW); 
        isOver = true; 
    }
    else if (!t2) { 
        TerminalUI::printLine("\n[WINNER] TEAM 1 WINS!", Color::LIGHT_BLUE); 
        isOver = true; 
    }
    else if (!t1) { 
        TerminalUI::printLine("\n[WINNER] TEAM 2 WINS!", Color::LIGHT_RED); 
        isOver = true; 
    }
    else if (round > 15) {
        int a1 = player1.countAlive(), a2 = player2.countAlive();
        TerminalUI::printLine("\n--- FINAL RESULT ---", Color::LIGHT_YELLOW);
        cout << "Team 1 alive: " << a1 << endl;
        cout << "Team 2 alive: " << a2 << endl;
        
        if (a1 > a2) TerminalUI::printLine("\nTEAM 1 WINS! (" + to_string(a1) + " alive)", Color::LIGHT_BLUE);
        else if (a2 > a1) TerminalUI::printLine("\nTEAM 2 WINS! (" + to_string(a2) + " alive)", Color::LIGHT_RED);
        else TerminalUI::printLine("\nDRAW! (" + to_string(a1) + " alive each)", Color::LIGHT_YELLOW);
        isOver = true;
    }
    
    if (isOver) {

        cout << "\n--- FINAL STATUS ---" << endl;
        cout << "Team 1: ";
        for (auto h : player1.getheroes()) {
            cout << h->getName() << (h->isAlive() ? "[ALIVE]" : "[DEAD]") << " ";
        }
        cout << "\nTeam 2: ";
        for (auto h : player2.getheroes()) {
            cout << h->getName() << (h->isAlive() ? "[ALIVE]" : "[DEAD]") << " ";
        }
        cout << endl;
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
        if (!isOver) {

            executeTurn(player2, player1, 2);
        }
    } else {
        executeTurn(player2, player1, 2);
        if (!isOver) {
            executeTurn(player1, player2, 1);
        }
    }

    for (auto h : player1.getheroes()) h->updateshield();
    for (auto h : player2.getheroes()) h->updateshield();

    for (auto h : player1.getheroes()) {
        if (h->getIsHidden() && h->getTargetRound() == round) {
            h->setHidden(false);
            h->setTargetRound(-1);
            cout << h->getName() << " is no longer hidden!" << endl;
        }
    }
    for (auto h : player2.getheroes()) {
        if (h->getIsHidden() && h->getTargetRound() == round) {
            h->setHidden(false);
            h->setTargetRound(-1);
            cout << h->getName() << " is no longer hidden!" << endl;
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
    if (!isOver) { 
        cout << "\n--- End of Round " << (round-1) << " ---" << endl;
        cout << "Press Enter for next round..."; 
        cin.ignore(); 
        cin.get(); 
    }
}

void game::startGame() {
    srand(time(nullptr));
    TerminalUI::clearScreen();
    TerminalUI::header("HERO BATTLE GAME");
    TerminalUI::printLine("Welcome to the Hero Battle Game!", Color::LIGHT_YELLOW);
    TerminalUI::printLine("Each team selects 3 heroes and they fight!", Color::LIGHT_BLUE);
    TerminalUI::printLine("Max 15 rounds per game.", Color::LIGHT_GREEN);
    TerminalUI::printLine("\nRules:", Color::LIGHT_YELLOW);
    cout << "- Each hero can only be selected once per team" << endl;
    cout << "- Energy resets each round" << endl;
    cout << "- Rage builds up and enables special abilities" << endl;
    cout << "- First team to eliminate all enemies wins" << endl;
    
    cout << "\nPress Enter to start hero selection...";
    cin.get();
    
    chooseHeroes();
    
    while (!isOver && round <= 15) {
        playRound();
    }

    if (!isOver && round > 15) {
        checkWinner();
    }
    
    TerminalUI::printLine("\nThanks for playing!", Color::LIGHT_YELLOW);
    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();
}