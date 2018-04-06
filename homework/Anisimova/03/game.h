#include <string>
#include <set>

class Existence
{
private:
    const std::string name;
    unsigned hp, attack, defense;
public:
    Existence(const std::string & name, unsigned hp, unsigned attack, unsigned defense);
    virtual ~Existence() = default;
};

class Human;

class Item
{
private:
    const std::string name;
    unsigned brokenness;
    const unsigned firmness;
    Human * owner;
    bool broken;
public:
    Item(const std::string & name, unsigned firm);
    virtual ~Item() = default;
    virtual std::string NameOfClass() const = 0;
    void Destroy(unsigned br);
    void SetOwner(Human * ptr);
    Human * GetOwner() const;
    void RemoveOwner();
};

class Arsenal: public Item
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

class Armor: public Item
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

class Human: public Existence
{
private:
    bool gender;
    Arsenal * ars;
    Armor * arm;
    unsigned exp;
    std::set<std::string> arsenals;
    std::set<std::string> armors; 
public:
    Human(const std::string & name, bool gender, unsigned hp, unsigned attack, unsigned defense, const std::set<std::string> & arsenals, const std::set<std::string> & armors);
    ~Human();
    void TakeArsenal(Arsenal * pars);
    void TakeArmor(Armor * parm);
    void RemoveArsenal();
    void RemoveArmor();
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

class Animal: public Existence
{
public:
    Animal(const std::string & name, unsigned hp, unsigned attack, unsigned defense);
};

class Pig: public Animal
{
private:
    const static unsigned pig_hp, pig_attack, pig_defense;
public:
    Pig(const std::string & name, bool gender);
};


