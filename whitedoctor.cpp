#include "whitedoctor.hpp"
#include <string>
#include <iostream>
using namespace std;

WhiteDoctor::WhiteDoctor() : hero("White Doctor", 550, 4) {};

WhiteDoctor::ability1(hero& enemyTarget, hero& allyTarget) {
    cout << getName() << " uses asprin on " << enemyTarget.getName() << "!" << endl;
    enemyTarget.takeDamage(40);

    cout << getName() << " heals " << allyTarget.getName() << " with asprin!" << endl;
    allyTarget.heal(40);   
    energy -= 3;
}

WhiteDoctor::ability2(hero& enemyTarget, hero& allyTarget) {
    cout << getName() << "uses doping " << endl;
    

}