//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_PEASENT_H
#define RPG_PEASENT_H


#include "Character.h"
#include "../armors/Robe.h"
#include "../weapons/Pike.h"

class Barbarian: public Character {
public:
    Barbarian():Character(40, new Pike(), new Robe()){};
};


#endif //RPG_PEASENT_H
