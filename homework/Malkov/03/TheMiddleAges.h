class Item {
    const std::string name;
    const unsigned int max_durability;
    unsigned int durability;
    bool broken;
};

class Weapon : public Item {
    const unsigned int damage;
};

class Sword : public Weapon {};

class Bow : public Weapon {};

class Knife : public Weapon {};

class Armor : public Item {
    const unsigned int defence;
};

class Vest : public Armor {};

class Harness : public Armor {};

class Mail : public Armor {};

class Shield : public Armor {};

class Alive {
    const unsigned int max_hp;
    const bool gender;
    const unsigned int own_damage;
    const unsigned int own_defence;
    unsigned int hp;
};

class Animal : public Alive {
    bool agressive;
    bool domesticated;
};

class Pig : public Animal {};

class Dog : public Animal {};

class Wolf : public Animal {};

class Human : public Alive {
    const std::string name;
    unsigned int age;
    Weapon weapon;
    Armor armor;
};

class Knight : public Human {};

class Archer : public Human {};

class Peasant : public Human {};
