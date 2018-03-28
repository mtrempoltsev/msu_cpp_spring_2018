//
// Created by User on 24.03.2018.
//

#ifndef RPG_H_RPG_H
#define RPG_H_RPG_H

#include <iostream>

class Loot {
    const std::string name;
    unsigned int durability;
    bool broken;
};

class Weapon : public Loot {
    const unsigned int damage;
};

class Sword : public Weapon {};

class Bow : public Weapon {};

class Shovel : public Weapon {};

class Armor : public Loot {
    const unsigned int defence;
};

class Hauberk : public Armor {};

class Lats : public Armor {};


class Arena{
    const unsigned int max_capacity;
    bool open_or_close;
};

class Audience : public Arena{
    unsigned int money;
    const unsigned int age;
    bool gender;
};

class Heroes : public Arena{
    const unsigned int max_hp;
    const bool gender;
    const unsigned int own_damage;
    const unsigned int own_defence;
    unsigned int hp;
};

class Animal : public Heroes {
    bool agressive;
    bool domesticated;
};

class Pig : public Animal {};

class Dog : public Animal {};

class Wolf : public Animal {};

class Human : public Heroes {
    const std::string name;
    unsigned int age;
    Weapon weapon;
    Armor armor;
};

class Knight : public Human {};

class Archer : public Human {};

class Peasant : public Human {};
#endif
