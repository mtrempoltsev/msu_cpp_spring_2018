//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_ARCHER_H
#define RPG_ARCHER_H


#include "Character.h"
#include "../armors/ChainMail.h"
#include "../weapons/Bow.h"

class Archer : public Character{
public:
    Archer():Character(20, new Bow(), new ChainMail()){}
};


#endif //RPG_ARCHER_H
