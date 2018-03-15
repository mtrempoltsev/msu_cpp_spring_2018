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



class sword : public Weapon {

};



class bow : public Weapon {

};



class shovel : public Weapon {

};



class Armor : public Thing {

    unsigned defense;

};



class lats : public Armor {

};



class chain_armor : public Armor {

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



class pig : public Animal {

};



class horse : public Animal {

};



class Human : public Creature {

    Armor* arms;

    Weapon* weapons;

    Animal* animals;

};



class peasant : public Human {

};



class archer : public Human {

};



class knight : public Human {

};
