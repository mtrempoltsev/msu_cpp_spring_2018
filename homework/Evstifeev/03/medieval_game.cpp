#include <iostream>

class Thing {
   public:
    Thing(int durability_) : durability{durability_} {}
    const bool isBroken() const { return durability <= 0; }
    void update(int upgrade) { durability += durability; }
    int durability;
};

// Weapons
class Weapon : public Thing {
   public:
    Weapon(int damage_, int durability_)
        : Thing(durability_), damage{damage_} {}
    virtual int powerAttack() { return damage; };
    int damage;
};

class Shovel : public Weapon {
   public:
    Shovel() : Weapon(10, 30) {}
};

class Sword : public Weapon {
   public:
    Sword() : Weapon(60, 80) {}
    int powerAttack() override { return 2 * damage; }
};

class Bow : public Weapon {
   public:
    Bow() : Weapon(45, 70) {}
};

// Armors
class Armor : public Thing {
   public:
    Armor(int defence_, int durability_)
        : Thing(durability_), defence{defence_} {}
    int defence;
};

class Mail : public Armor {
   public:
    Mail() : Armor(70, 80){};
};

class Plate : public Armor {
   public:
    Plate() : Armor(50, 70){};
};

class NPC {
   public:
    NPC(std::string name_) : health{100}, name{name_} {}
    bool interact(NPC* npc);
    int health;
    bool isDead() { return health <= 0; }
    std::string name;
};

// Characters
class Character : public NPC {
   public:
    Character(std::string name_) : NPC(name_) {}
    Weapon* getWeapon() { return weapon; }
    void setWeapon(Weapon* weapon_) { weapon = weapon_; }
    Armor* getArmor() { return armor; }
    void setArmor(Armor* armor_) { armor = armor_; }
    void powerAttack(NPC* npc) { npc->health -= weapon->powerAttack(); }
    void attack(NPC* npc) {
        if (weapon->isBroken()) {
            npc->health -= 1;  // fists damage;
        } else {
            npc->health -= weapon->damage;
            weapon->durability -= 5;
        }
    }

   private:
    Weapon* weapon;
    Armor* armor;
};

class Peasant : public Character {
   public:
    Peasant(std::string name_) : Character(name_) { setWeapon(new Shovel()); }
};

class Archer : public Character {
   public:
    Archer(std::string name_) : Character(name_) {
        setWeapon(new Bow());
        setArmor(new Mail());
    }
};

class Knight : public Character {
   public:
    Knight(std::string name_) : Character(name_) {
        setWeapon(new Sword());
        setArmor(new Plate());
    }
};

class Animal : public NPC {
   public:
    Animal(std::string name_) : NPC(name_) {}
    void doNothing() { std::cout << "Doing nothin'"; }
};

class Pig : public Animal {
   public:
    Pig(std::string name_) : Animal(name_) {}
};

class Horse : public Animal {
   public:
    Horse(std::string name_) : Animal(name_) {}
};

int main() {
    Knight knight{"King Arthur"};
    Peasant peasant{"Ulric"};
    std::cout << "Peasant health: " << peasant.health << std::endl;
    std::cout << "Knight attacked peasant with sword: damage="
              << knight.getWeapon()->damage;
    std::cout << " and durability=" << knight.getWeapon()->durability
              << std::endl;
    knight.attack(&peasant);
    std::cout << "Peasant health now: " << peasant.health << std::endl;
    std::cout << "Sword's durability:  " << knight.getWeapon()->durability
              << std::endl;
}
