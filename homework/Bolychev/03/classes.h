#include <string>
#include <vector>

class Item{
    std::string name;
    int corruption;
};

class Weapon:Item {
    int attack;
};

class Bow:Weapon {};

class Sword:Weapon {};

class Food:Item {
    int energy;
};

class Armour:Item{
    int defence;
};

class Being {
    int health;
    std::string name;
};

class Human:Being {
    vector<Item> inventory;
    Weapon weapon;
    Armour armour;
};

class Animal:Being {};

class Horse:Animal {};

class Pig:Animal {};
