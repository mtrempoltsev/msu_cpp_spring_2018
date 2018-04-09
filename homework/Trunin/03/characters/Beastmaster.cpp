//
// Created by Alex on 18.03.2018.
//

#include "Beastmaster.h"

void Beastmaster::attack(Character* character) {
    int weaponDmg = this->weapon->hit();
    if (increasedAttack){
        weaponDmg += 2;
    }
    int dmg = weaponDmg - character->armor->getDefence();
    character->armor->takeDmg(weaponDmg);
    if(dmg > 0) {
        character->hp = (character->hp - dmg);
    }
}

void Beastmaster::summonBird(){
    increasedAttack = false;
    if(animal != nullptr){
        delete animal;
    }

    animal = new Bird();

}

void Beastmaster::summonPig(){
    if(animal != nullptr){
        delete animal;
    }
    animal = new Pig();
}

void Beastmaster::useAnimal(){
    if(typeid(*animal) == typeid(Pig)){
        increasedAttack = true;
    }
    if(typeid(*animal) == typeid(Bird)){
        hp += 5;
    }
}

void Beastmaster::showInfo(){
    Character::showInfo();
    std::cout << "Increased Attack " << increasedAttack << std::endl;
    if(typeid(*animal) == typeid(Pig)) {
        std::cout << "Current Animal Pig" << std::endl;
        return;
    }
    if (typeid(*animal) == typeid(Bird)) {
        std::cout << "Current Animal Bird" << std::endl;
        return;
    }
}