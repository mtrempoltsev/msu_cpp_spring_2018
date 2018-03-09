#ifndef MEDIEVAL_H
#define MEDIEVAL_H

#include <typeinfo>
#include <string>
#include <set>

class Alive
{
private:
    const std::string name;
    unsigned hp, atk, dfn;
public:
    Alive(const std::string & name, unsigned hp, unsigned atk, unsigned dfn);
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
    void Destruct();
    void Destroy(unsigned br);
public:
    Thing(const std::string & name, unsigned firm);
    ~Thing();
    friend void Battle(Alive * comp1, Alive * comp2);
    friend class Human;
protected:
    void SetOwner(Human * ptr);
    Human * GetOwner() const;
};

class Arsenal: public Thing
{
private:
    unsigned atk;
    void Destruct();
public:
    Arsenal(const std::string & name, unsigned firm, unsigned atk);
    ~Arsenal();
    friend class Human;
};

class Shovel: public Arsenal
{
};

class Sword: public Arsenal
{
};

class Arch: public Arsenal
{
};

class Armor: public Thing
{
private:
    unsigned dfn;
    void Destruct();
public:
    Armor(const std::string & name, unsigned firm, unsigned dfn);
    ~Armor();
    friend class Human;
};

class Lats: public Armor
{
};

class Chain: public Armor
{
};

class Human: public Alive
{
private:
    bool gender;
    Arsenal * ars;
    Armor * arm;
    unsigned exp;
    std::set<std::string> arsenals;
    std::set<std::string> armors; 
public:
    Human(const std::string & name, bool gender, unsigned hp, unsigned atk, unsigned dfn, const std::set<std::string> & arsenals, const std::set<std::string> & armors);
    ~Human();
    void TakeArsenal(Arsenal * pars);
    void TakeArmor(Armor * parm);
    friend class Arsenal;
    friend class Armor;
};

class Farmer: public Human
{
private:
    const static unsigned farmer_hp, farmer_atk, farmer_dfn;
public:
    Farmer(const std::string & name, bool gender);
};

class Knight: public Human
{
private:
    const static unsigned knight_hp, knight_atk, knight_dfn;
public:
    Knight(const std::string & name, bool gender);
};

class Archer: public Human
{
private:
    const static unsigned archer_hp, archer_atk, archer_dfn;
public:
    Archer(const std::string & name, bool gender);
};

class Animal: public Alive
{
public:
    Animal(const std::string & name, unsigned hp, unsigned atk, unsigned dfn);
    ~Animal();
};

class Pig: public Animal
{
private:
    const static unsigned pig_hp, pig_atk, pig_dfn;
public:
    Pig(const std::string & name, bool gender);
};

#endif
