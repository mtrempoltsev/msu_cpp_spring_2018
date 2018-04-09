//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_WEAPON_H
#define RPG_WEAPON_H

#include <iostream>

class Weapon {
private:
    int dmg;
    int durability;
    int durabilityMax;
public:
    Weapon(int dmg_, int durability_):dmg(dmg_), durability(durability_), durabilityMax(durability_){}
    int hit();
    void repair();
    void showInfo();
};


#endif //RPG_WEAPON_H
