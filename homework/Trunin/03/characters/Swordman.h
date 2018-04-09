//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_SWORDMAN_H
#define RPG_SWORDMAN_H

#include "Character.h"
#include "../armors/Lats.h"
#include "../weapons/Sword.h"

class Swordman: public Character {
public:
    Swordman():Character(30, new Sword(), new Lats()){}
};


#endif //RPG_SWORDMAN_H
