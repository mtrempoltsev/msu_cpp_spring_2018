class Human;



class Thing {

    string name;

    unsigned durability;

    unsigned dexterity;

    unsigned strength;

    bool broken;

    Human* owner;

};



class Weapon : public Thing {

    unsigned attack;

};



class Sword : public Weapon {

};



class Bow : public Weapon {

};



class Shovel : public Weapon {

};



class Armor : public Thing {

    unsigned defense;

};



class Lats : public Armor {

};



class Chain_armor : public Armor {

};



class Creature {

    string name;

    unsigned max_health;

    unsigned health;

    unsigned defense;

    bool gender;

    unsigned age;

    unsigned dexterity;

    unsigned strength;

};



class Animal : public Creature {

    Human* owner;

};



class Pig : public Animal {

};



class Horse : public Animal {

};



class Human : public Creature {

    Armor* arms;

    Weapon* weapons;

    Animal* animals;

};



class Peasant : public Human {

};



class Archer : public Human {

};



class Knight : public Human {

};
