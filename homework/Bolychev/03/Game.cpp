#include <iostream>

class Item {
public:
    std::string name;
    int durability;

    Item(const std::string& name_, const int durability_)
            : name(name_), durability(durability_) {}

    const bool isCorrupted() const { return durability <= 0; }
};

class Food: public Item {
public:
    int energy;

    Food(const std::string& name_, const int durability_, const int energy_)
            : Item(name_, durability_), energy(energy_) {}
};

class Meat: public Food {
public:
    Meat() : Food("Meat", 3, 50) {}
};

class Apple : public Food {
public:
    Apple() : Food("Apple", 7, 20) {}
};

class Weapon : public Item {
public:
    int damage;

    Weapon(const std::string& name_, const int durability_, const int damage_)
            : Item(name_, durability_), damage(damage_) {}
};

class Shovel : public Weapon {
public:
    Shovel() : Weapon("Shovel", 100, 20) {}
};

class Sword : public Weapon {
public:
    Sword() : Weapon("Sword", 100, 60) {}
};

class Bow : public Weapon {
public:
    Bow() : Weapon("Bow", 100, 45) {}
};

// Armors
class Armour : public Item {
public:
    int defence;
    Armour(const std::string& name_, const int durability_, const int defence_)
            : Item(name_, durability_), defence(defence_) {}
};

class Mail : public Armour {
public:
    Mail() : Armour("Mail", 80, 70) {}
};

class Plate : public Armour {
public:
    Plate() : Armour("Plate", 70, 50) {}
};

class Being {
public:
    std::string name;
    int health;

    Being(std::string name_) : name(name_), health(100) {}
    bool isAlive() const { return health > 0; }
};

// Characters
class Human : public Being {
public:
    Human(std::string name_) : Being(name_) {}

    Weapon* getWeapon() const { return weapon; }
    Armour* getArmor() const { return armour; }

    void setWeapon(Weapon* weapon_) { weapon = weapon_; }
    void setArmor(Armour*armour_) { armour = armour_; }

    void eat(Food* food_item) {
        if (food_item->isCorrupted()) {
            health -= 5;
        } else {
            health += food_item->energy;
            health %= 100;
        }

        delete food_item;
    }

    void attack(Being& npc) {
        if (weapon->isCorrupted()) {
            npc.health -= 1;  // fists damage;
        } else {
            npc.health -= weapon->damage;
            weapon->durability -= 5;
        }
    }

private:
    Weapon* weapon;
    Armour*armour;
};

class Animal : public Being {
public:
    Animal(const std::string& name_) : Being(name_) {}
};

class Horse : public Animal {
public:
    Horse(const std::string& name_) : Animal(name_) {}
};

class Pig : public Animal {
public:
    Pig(const std::string& name_) : Animal(name_) {}
};

class Knight : public Human {
public:
    Knight(const std::string& name_) : Human(name_) {
        setWeapon(new Sword());
        setArmor(new Plate());
    }
};

class Archer : public Human {
public:
    Archer(const std::string& name_) : Human(name_) {
        setWeapon(new Bow());
        setArmor(new Mail());
    }
};

class Peasant : public Human {
public:
    Peasant(const std::string& name_) : Human(name_) { setWeapon(new Shovel()); }
};


int main() {
    Peasant durak("Ivanushka Durachok");
    Knight popovich("Alexey Popovich");

    auto piece_of_meat = new Meat();

    std::cout << "Game begins:\n=========================\n\n";
    std::cout << durak.name << "'s health: " << durak.health << std::endl;
    std::cout << popovich.name << "'s health: " << popovich.health << std::endl;

    std::cout << "\nPopovich got angry with Ivanushka Durachok and hit him with a " <<
        popovich.getWeapon()->name << " with damage = " <<
        popovich.getWeapon()->damage << " and durability = " <<
        popovich.getWeapon()->durability << std::endl;

    popovich.attack(durak);

    std::cout << "And now Durak's health equals " << durak.health << std::endl;

    std::cout << "\nBut Ivan found a piece of meat and he is gonna eat it\n" << std::endl;
    durak.eat(piece_of_meat);

    std::cout << "Ivan's health now is quite OK: " << durak.health << std::endl;

    std::cout << "But " << popovich.getWeapon()->name <<"'s durability equals now  " <<
            popovich.getWeapon()->durability << std::endl;

    std::cout << "\n=========================\nGame over" << std::endl;

    return 0;
}