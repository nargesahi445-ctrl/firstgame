#pragma once
#include "team.hpp"
#include "whitedoctor.hpp"
#include "littletaha.hpp"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class game {
    
    private:
        team player1;
        team player2;
        int round = 1;
        bool isOver = false;
        vector<int> energyPattern1 = {5, 9, 10};
        vector<int> energyPattern2 = {8, 9, 10};
        int firstTeam = 1;
        bool firstTurnSet = false;

    public:
        int getround() const { return round; }
        bool roundhasended(int roundnum) const;
        void chooseHeroes();
        void playRound();
        void startGame();
        void checkWinner();
        void handleUnhiding(team& myteam);
        void updateOngoingEffects();
        int getEnergyForTeam(int teamNum) const;
        bool isGameOver() const { return isOver; }
        void displayStatus() const;
        void executeTurn(team& attackingTeam, team& defendingTeam, int teamNum);
        hero* selectTarget(team& enemyTeam);
        hero* selectAlly(team& myTeam, hero* currentHero);
        bool showAbilityMenu(hero* currentHero, team& myTeam, team& enemyTeam, game& currentGame, int teamNum);
};