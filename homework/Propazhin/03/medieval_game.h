class Item
{
    int item_id;
    const int max_durability;
    int durability;
    bool broken;
};

class Weapon: public Item
{
    const int range;
    const int damage;
    Weapon(){}
    ~Weapon(){}
};

class Shovel: public Weapon{};
class Sword: public Weapon{};
class Bow: public Weapon{};

class Armor: public Item
{
    const int effiency;
    Armor() {}
    ~Armor() {}
};

class ChainArmor: public Armor{};
class Plate: public Armor{};

class Creature
{
    int creature_id;
    const int max_HP;
    const int max_XP;
    int HP;
    int XP;
    Creature(){}
    virtual ~Creature(){}
};

class Animal: public Creature
{
    bool type; // peaceful(0) or agressive(1)
    int damage;
};

class Human: public Creature
{
    int damage;
    Weapon weapon;
    Armor armor;
};

class Peasant: public Human{};

class Archer: public Human
{
    Archer() { weapon = new Bow(); armor  = new ChainArmor();}
    ~Archer(){delete weapon; delete armor;}
};

class Knight: public Human
{
    Knight() { weapon = new Sword(); armor = new Plate();}
    ~Knight() {delete weapon; delete armor;}
};

class Pig: public Animal{};
class Dog: public Animal{};
class Horse: public Animal{};


