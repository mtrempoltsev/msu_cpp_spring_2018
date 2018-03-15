#include <string>
#include <vector>

class Object {
protected:
    std::string name;
    std::pair<int, int> position;
};

//-----------------------Creature-----------------------------------
class Creature : public Object {
protected:
    int health_points;
    int mana_points;
    int base_armor;
    float speed;
    int id_c;
    int weight_capacity;
};

class NPC : public Creature {
};

class Human : public Creature {
protected:
    int base_damage;
    int base_stamina;
    bool have_wep;
    std::vector<Weapon *> base_weapons;
    bool have_animal;
    std::vector<Animal *> animals;
};

class Archer : public Human {
private:
    float damage_modifier;
};

class Knight : public Human {
private:
    float stamina_modifier;
};

class Sorcerer : public Human {
private:
    std::vector<Cast *> spells;
    float spd_modifier;
};

class Peasant : public Human {
private:
	std::string area;
};

//-----------------------Animal-------------------------
class Animal : public Creature {
protected:
    bool have_owner;
    Human *owner;

};

class Cat : public Animal {
private:
	int lives;
};

class Pig : public Animal {
};

class Unicorn : public Animal {
private:
    std::vector<Cast *> spells;
};

//-----------------------Usable-------------------------
class Item : public Object {
protected:
    int durability;
    int koeff_durability;
    int id_i;
    Human *owner;
    float weight;
};

class Weapon : public Item {
protected:
    int damage;
    float distance;
    int stamina_take;
};

class Sword : public Weapon {
private:
	float length;
};

class Bowl : Weapon {
private:
    int arrows;
};

class knife : public Weapon {
};

enum Body_parts {
    HEAD, BODY, ARMS, LEGS
};

class Armor : public Item {
    int armor;
    Body_parts cell;
};

class Hemlet : public Armor {
};

class Chainmail : public Armor {
private:
	std::string effect;
};

class Breastplates : public Armor {
private:
	std::string passive;
};

class Unusable_Item : public Object {
protected:
    float Volume;
    float area;
};

class House : public Unusable_Item {
};

class Tree : public Unusable_Item {
};


class Magic : public Object {
    int force;
    int distance;
};

class Cast : public Magic {
protected:
    std::string action;
    int damage;
    int heal;
};
	
	
	
	
	
	
