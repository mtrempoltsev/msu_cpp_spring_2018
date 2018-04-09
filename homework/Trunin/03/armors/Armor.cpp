//
// Created by Alex on 18.03.2018.
//

#include "Armor.h"

int Armor::getDefence() const {
    if(isBroken){
        return 0;
    }
    return defence;
}

void Armor::takeDmg(int dmg){
    if(isBroken){
        return;
    }
    defence = defence - dmg;
    if (defence <= 0){
        isBroken = true;
    }
}

void Armor::repair() {
    isBroken = false;
    defence = maxDefence;
}

void Armor::showInfo() {
    std::cout << "isBroken: " << isBroken << std::endl;
    std::cout << "Defence: " << defence << std::endl;
    std::cout << "Max Defence: " << maxDefence << std::endl;
}
