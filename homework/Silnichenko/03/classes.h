#include <iostream>

class Item
{
	public:
    std::string name_;
    int durability_;
    Item(const std::string& name, const int durability)
            : name_(name), durability_(durability) {}
    const bool isCorrupted() const { return durability_ <= 0; }
};

class Food: public Item 
{
	public:
    int energy_;
    Food(const std::string& name, const int durability, const int energy)
            : Item(name, durability), energy_(energy) {}
};

class Meat: public Food
{
	public:
    Meat() : Food("Meat", 3, 50) {}
};

class Apple : public Food 
{
	public:
    Apple() : Food("Apple", 7, 20) {}
};

class Weapon : public Item 
{
	public:
    int damage_;
    Weapon(const std::string& name, const int durability, const int damage)
            : Item(name, durability), damage_(damage) {}
};

class Shovel : public Weapon 
{
	public:
    Shovel() : Weapon("Shovel", 100, 20) {}
};

class Sword : public Weapon 
{
	public:
    Sword() : Weapon("Sword", 100, 60) {}
};

class Bow : public Weapon 
{
	public:
    Bow() : Weapon("Bow", 100, 45) {}
};

// Armours
class Armour : public Item 
{
	public:
    int defence_;
    Armour(const std::string& name, const int durability, const int defence)
            : Item(name, durability), defence_(defence) {}
};

class Mail : public Armour 
{
	public:
    Mail() : Armour("Mail", 80, 70) {}
};

class Plate : public Armour 
{
	public:
    Plate() : Armour("Plate", 70, 50) {}
};

class Being 
{
	public:
    std::string name_;
    int health_;
    Being(std::string name) : name_(name), health_(100) {}
    bool isAlive() const { return health > 0; }
};

// Characters
class Human : public Being 
{
	public:
    Human(std::string name) : Being(name) {}

    Weapon* getWeapon() const { return weapon_; }
    Armour* getArmor() const { return armour_; }

    void setWeapon(Weapon* weapon) { weapon_ = weapon; }
    void setArmor(Armour*armour) { armour_ = armour; }

    void eat(Food* food_item) {
        if (food_item->isCorrupted()) {
            health_ -= 5;
        } else {
            health_ += food_item->energy_;
            health_ %= 100;
        }

        delete food_item;
    }

    void attack(Being& npc) {
        if (weapon_->isCorrupted()) {
            npc.health_ -= 1;  //damage dealt w fists;
        } else {
            npc.health_ -= weapon_->damage;
            weapon_->durability_ -= 5;
        }
    }

private:
    Weapon* weapon_;
    Armour* armour_;
};

class Animal : public Being 
{
	public:
    Animal(const std::string& name) : Being(name) {}
};

class Horse : public Animal 
{
	public:
    Horse(const std::string& name) : Animal(name) {}
};

class Pig : public Animal 
{
	public:
    Pig(const std::string& name) : Animal(name) {}
};

class Knight : public Human 
{
	public:
    Knight(const std::string& name) : Human(name) {
        setWeapon(new Sword());
        setArmor(new Plate());
    }
};

class Archer : public Human 
{
	public:
    Archer(const std::string& name) : Human(name) {
        setWeapon(new Bow());
        setArmor(new Mail());
    }
};

class Peasant : public Human 
{
	public:
    Peasant(const std::string& name) : Human(name) { setWeapon(new Shovel()); }
};
