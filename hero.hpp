#include<iostream>
using namespace std;

class hero {
    private:
        string name;
        int hp;
        int rage;
        int maxhp;
        int rager;
        int currage;

    public:
        hero(string name , int hp , int energy);

        virtual ~hero() = default;

        virtual void ability1(hero& enemyTarget, hero& allyTarget) = 0;
        virtual void ability2(hero& enemyTarget, hero& allyTarget , game& , int ) = 0;
        virtual void specialability(hero& enemyTarget, hero& allyTarget) = 0;

        void takeDamage(int amount);
        void heal(int amount);

        bool isAlive() const;

        int getHP() const;
        std::string getName() const;

        void increaserage();
        bool canusespecial() const;
        void resetrage();
    };



    
