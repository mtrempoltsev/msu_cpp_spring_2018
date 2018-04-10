//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H

#include "../armors/Armor.h"
#include "../weapons/Weapon.h"
#include <iostream>

class Character {
public:
    int hp;
    Weapon* weapon;
    Armor* armor;
public:
    Character(int hp_, Weapon* weapon_, Armor* armor_):
            hp(hp_), weapon(weapon_), armor(armor_){};

    virtual void attack(Character* character);
    void repairWeapon();
    void repairArmor();
    virtual void showInfo();
};


#endif //RPG_CHARACTER_H
