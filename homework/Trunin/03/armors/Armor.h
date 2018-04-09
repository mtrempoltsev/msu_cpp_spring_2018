//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_ARMOR_H
#define RPG_ARMOR_H

#include <iostream>

class Armor {
private:
    int defence;
    int maxDefence;
    bool isBroken = false;
public:
    Armor(int defence_):defence(defence_),maxDefence(defence_){}
    int getDefence() const;
    void takeDmg(int dmg);
    void repair();
    void showInfo();
};


#endif //RPG_ARMOR_H
