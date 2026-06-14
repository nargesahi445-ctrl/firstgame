#pragma once
#include<iostream>
#include "game.hpp"
using namespace std;

class hero {
    private:
        string name;
        int shield = 0;
        int shieldTurn = 0;
        int hp;
        int maxhp;
        int rager;
        int currage;

    public:
        hero(string name , int hp , int energy);

        virtual ~hero() = default;

<<<<<<< HEAD
        virtual void ability1(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam) = 0;
        virtual void ability2(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam) = 0;
        virtual void specialability(hero& enemyTarget, hero& allyTarget ,team& enemyteam, team& myteam) = 0;
=======
        virtual void ability1(hero& enemyTarget, hero& allyTarget) = 0;
        virtual void ability2(hero& enemyTarget, hero& allyTarget , game& , int ) = 0;
        virtual void specialability(hero& enemyTarget, hero& allyTarget) = 0;
>>>>>>> ab9a1fb6c20debed0abf52f04e7edf8f24aa2d38

        void takeDamage(int amount);
        void heal(int amount);

        bool isAlive() const;

        int getHP() const;
        std::string getName() const;

        void addshield(int amount , int turn);
        void increaserage();
        void updateshield();
        bool canusespecial() const;
        void resetrage();
    };

    
