
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
    Armor *armor;
    Weapon *weapon;
    Animal *animal
};

class Animal: public Animate
{
    Humans *owner;
};

class Pig: public Animal {

};

class Knight: public Humans {

};

class Archer: public Humans{

};

class Peasant: public Humans{

};



