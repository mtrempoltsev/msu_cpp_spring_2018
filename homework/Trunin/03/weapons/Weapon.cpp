//
// Created by Alex on 18.03.2018.
//

#include "Weapon.h"

int Weapon::hit() {
    if (durability <= 0){
        return 0;
    }
    durability--;
    return dmg;
}

void Weapon::repair() {
    durability = durabilityMax;
}

void Weapon::showInfo(){
    std::cout << "Durability: " << durability << std::endl;
    std::cout << "Durability Max: " << durabilityMax << std::endl;
    std::cout << "Dmg: " << dmg << std::endl;
}
