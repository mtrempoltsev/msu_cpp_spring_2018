//
// Created by Alex on 18.03.2018.
//

#ifndef RPG_BEASTMASTER_H
#define RPG_BEASTMASTER_H


#include "Character.h"
#include "../animals/Animal.h"
#include "../armors/Robe.h"
#include "../weapons/Pike.h"
#include "../animals/Pig.h"
#include "../animals/Bird.h"
#include <typeinfo>

class Beastmaster: public Character {
private:
    Animal* animal;
    bool increasedAttack = false;
public:
    Beastmaster():Character(30, new Pike(), new Robe()){
        animal = new Pig();
    }
    void summonBird();
    void summonPig();
    virtual void attack(Character* character) override;
    void useAnimal();
    virtual void showInfo();
};


#endif //RPG_BEASTMASTER_H
