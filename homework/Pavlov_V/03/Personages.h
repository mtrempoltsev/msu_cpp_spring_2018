#include <iostream>


class Object {
    
};

class Personage: public Object {
protected:
    std::string name;
    int hp;
public:
    Personage(std::string, int);
    Personage(): name("user"), hp(100) { };
    std::string getName();
    int getHp();
};

class Animals: public Personage {
protected:
    std::string kind;
};

class Pig: public Animals {
private:
    std::string breed;
public:
    Pig(): breed("") { };
};

class Equipment: public Object {
protected:
    int countArmor;
    int countDamage;
public:
    int getCountArmor();
    int getCountDamage();
};


class Human: public Personage {
protected:
    Equipment eq;
public:
    void takeWeapon();
    void turfWeapon();
    void takeArmor();
    void turfArmor();
};

class Peasant: public Human {
public:
    Peasant(std::string);
};

class Archer: public Human {
private:
    int rangeOfFire;
public:
    Archer(int);
};

class Knight: public Human {
private:
    int weight;
public:
    Knight(int);
};

class Weapon: public Equipment {
protected:
    int damage;
};

class Shovel: public Weapon {
public:
    Shovel(int);
};

class Sword: public Weapon {
public:
    Sword(bool);
};

class Bow: public Weapon {
public:
    Bow(int);
};


class Armor: public Equipment {
protected:
    int armor;
};

class Hauberg: public Armor {
public:
    Hauberg(int);
};

class Armour: public Armor {
public:
    Armour(int);
};

