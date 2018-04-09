//
// Created by Alex on 18.03.2018.
//

#include "Character.h"

void Character::attack(Character* character) {
    int weaponDmg = this->weapon->hit();
    int dmg = weaponDmg - character->armor->getDefence();
    character->armor->takeDmg(weaponDmg);
    if(dmg > 0) {
        character->hp = (character->hp - dmg);
    }
}

void Character::repairArmor() {
    this->armor->repair();
}

void Character::repairWeapon() {
    this->weapon->repair();
}

void Character::showInfo() {
    std::cout << "Hp: " << this->hp << std::endl;
    this->armor->showInfo();
    this->weapon->showInfo();
}