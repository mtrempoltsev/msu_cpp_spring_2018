
class Inanimate
{
    const std::string name;
    const int max_durability;
    int durability;
};

class Weapon: public Inanimate
{
    const int damage;
    const int speed;
};

class Shovel: public Weapon {

};

class Sword: public Weapon {

};

class Bow: public Weapon {

};

class Armor: public Inanimate
{
    const int defence;
};

class Lats: public Armor {

};

class ChainArmor: public Armor {

};

class Animate
{
    const std::string name;
    const int max_health;
    int health;
};

class Humans: public Animate
{
    const int damage;
    const int defence;
};

class Animal: public Animate
{
    const int damage;
};

class Pig: public Animal {
    Peasant *owner;
};

class Knight: public Humans
{
    Sword *weapon;
    Lats *armor;

};

class Archer: public Humans
{
    Bow *weapon;
    ChainArmor *armor;
};

class Peasant: public Humans
{
    Shovel *weapon;
    Pig *animal;
};



