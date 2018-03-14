#ifndef MEDIEVAL_H
#define MEDIEVAL_H

#include <string>
#include <set>

class Alive
{
private:
    const std::string name;
    unsigned hp, attack, defense;
public:
    Alive(const std::string & name, unsigned hp, unsigned attack, unsigned defense);
    virtual ~Alive() = default;
    friend void Battle(Alive * comp1, Alive * comp2);
};

class Human;

class Thing
{
private:
    const std::string name;
    unsigned brokenness;
    const unsigned firmness;
    Human * owner;
    bool broken;
    void Destroy(unsigned br);
public:
    Thing(const std::string & name, unsigned firm);
    virtual ~Thing() = default;
    friend void Battle(Alive * comp1, Alive * comp2);
    friend class Human;
    virtual std::string NameOfClass() const = 0;
protected:
    void SetOwner(Human * ptr);
    Human * GetOwner() const;
    void RemoveOwner();
};

class Arsenal: public Thing
{
private:
    unsigned attack;
public:
    Arsenal(const std::string & name, unsigned firm, unsigned attack);
    ~Arsenal();
};

class Shovel: public Arsenal
{
public:
    std::string NameOfClass() const override;
};

class Sword: public Arsenal
{
public:
    std::string NameOfClass() const override;
};

class Arch: public Arsenal
{
public:
    std::string NameOfClass() const override;
};

class Armor: public Thing
{
private:
    unsigned defense;
public:
    Armor(const std::string & name, unsigned firm, unsigned defense);
    ~Armor();
};

class Lats: public Armor
{
public:
    std::string NameOfClass() const override;
};

class Chain: public Armor
{
public:
    std::string NameOfClass() const override;
};

class Human: public Alive
{
private:
    bool gender;
    Arsenal * ars;
    Armor * arm;
    unsigned exp;
    /*
    множество имен классов тех типов оружия и доспехов, которые доступны данному классу людей, чтобы случайно крустьянин не взял меч; я предполагаю, что багажа нет, и всякую вещь можно либо надеть/взять в руки, либо выкинуть; кроме того предполагаю, что очень опытный крестьянин может взять меч, поэтому множества не статические
    */
    std::set<std::string> arsenals;
    std::set<std::string> armors; 
public:
    Human(const std::string & name, bool gender, unsigned hp, unsigned attack, unsigned defense, const std::set<std::string> & arsenals, const std::set<std::string> & armors);
    ~Human();
    void TakeArsenal(Arsenal * pars);
    void TakeArmor(Armor * parm);
    void RemoveArsenal();
    void RemoveArmor();
    friend class Arsenal;
    friend class Armor;
};

class Farmer: public Human
{
private:
    const static unsigned farmer_hp, farmer_attack, farmer_defense;
public:
    Farmer(const std::string & name, bool gender);
};

class Knight: public Human
{
private:
    const static unsigned knight_hp, knight_attack, knight_defense;
public:
    Knight(const std::string & name, bool gender);
};

class Archer: public Human
{
private:
    const static unsigned archer_hp, archer_attack, archer_defense;
public:
    Archer(const std::string & name, bool gender);
};

class Animal: public Alive
{
public:
    Animal(const std::string & name, unsigned hp, unsigned attack, unsigned defense);
    ~Animal();
};

class Pig: public Animal
{
private:
    const static unsigned pig_hp, pig_attack, pig_defense;
public:
    Pig(const std::string & name, bool gender);
};

#endif
