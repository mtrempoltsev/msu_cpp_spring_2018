#include <string>

class LivingBeing
{
protected:
    unsigned attack, defence, hp;
    std::string name;

public:
    LivingBeing(const std::string &name, unsigned hp, unsigned attack, unsigned defense);
    ~LivingBeing();
};

class Animal : public LivingBeing
{
public:
     Animal(const std::string &name);
};

class Pig : public Animal
{
public:
    Pig(const std::string &name);
};

class Weapon
{
protected:
    unsigned attack, wearout, attack_range;

public:
    Weapon(unsigned attack, unsigned current_state, unsigned attack_range);
    ~Weapon();
};

class Shovel : public Weapon
{
public:
    Shovel() : Weapon(10, 100, 1){};
};

class Sword : public Weapon
{
public:
    Sword() : Weapon(70, 100, 2){};
};

class Bow : public Weapon
{
public:
    Bow() : Weapon(25, 100, 10){};
};

class Armor
{
protected:
    unsigned defence, current_state;

public:
    Armor(unsigned defence, unsigned current_state);
};

class Hauberk : public Armor
{
public:
    Hauberk() : Armor(10, 100){}
};

class Lats : public Armor
{
public:
    Lats() : Armor(20, 100){}
};

class Human : public LivingBeing
{
protected:
    bool gender, armed, armored;
    Armor *arm;
    Weapon *wpn;

public:
    Human(const std::string &name, unsigned hp, unsigned attack, unsigned defense, bool gender, Weapon *wpn, Armor *arm);
};

class Peasant : public Human
{
public:
    Peasant(const std::string &name, unsigned hp, unsigned attack, unsigned defense, bool gender, Weapon *wpn, Armor *arm);
};

class Swordsman : public Human
{
public:
    Swordsman(const std::string &name, unsigned hp, unsigned attack, unsigned defense, bool gender, Weapon *wpn, Armor *arm);
};

class Bowman : public Human
{
public:
    Bowman(const std::string &name, unsigned hp, unsigned attack, unsigned defense, bool gender, Weapon *wpn, Armor *arm);
};

 int main(void)
 {
     return 0;
 }
