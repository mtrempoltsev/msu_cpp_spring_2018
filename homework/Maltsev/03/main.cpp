#include <iostream>

class Alive {
private:
    int cur_health,
            max_health;
public:
    explicit Alive(uint hp = 100)
            : cur_health(hp), max_health(hp) {

    };

    void reduce_cur_hp(uint hp) {
        if (cur_health > hp) {
            cur_health -= hp;
        } else {
            cur_health = 0;
        }
    }

    void reduce_max_hp(uint hp) {
        if (max_health > hp) {
            cur_health -= hp;
            max_health -= hp;
        } else {
            max_health = 1;
            cur_health = 1;
        }
    }

    void increse_max_hp(uint hp) {
        max_health += hp;
    }

    void increse_cur_hp(uint hp) {
        auto tmp = cur_health + hp;
        cur_health = tmp > max_health ? max_health
                                      : tmp;
    }

    bool is_alive() const {
        return cur_health != 0;
    }

    uint get_cur_health() {
        return cur_health;
    }

    uint get_max_health() {
        return max_health;
    }

    friend std::ostream &operator<<(std::ostream &os, const Alive &al) {
        os << "cur_health = " << al.cur_health
                  << "; max_health = " << al.max_health
                  << std::endl;
        return os;
    }
};

class Animal :
        public Alive {
private:
    uint exp;
public:
    explicit Animal(uint hp = 100, uint exp = 50) : Alive(hp), exp(exp) {};

    uint get_exp() {
        return exp;
    }

    friend std::ostream &operator<<(std::ostream &os, const Animal &an) {
        os << dynamic_cast<const Alive&>(an)
                  << "exp = " << an.exp
                  << std::endl;
        return os;
    }

};

class Pig :
        public Animal {
public:
    explicit Pig(uint hp = 30, uint exp = 7)
            : Animal(hp, exp) {};

    friend std::ostream &operator<<(std::ostream &os, const Pig &pig) {
        os << "Pig "
                  << dynamic_cast<const Animal&>(pig)
                  << std::endl;
        return os;
    }
};

class Sheep :
        public Animal {
public:
    explicit Sheep(uint hp = 20, uint exp = 5)
            : Animal(hp, exp) {};

    friend std::ostream &operator<<(std::ostream &os, const Sheep &sheep) {
        os << "Sheep "
                  << dynamic_cast<const Animal&>(sheep)
                  << std::endl;
        return os;
    }
};

class Item {
private:
    uint durability;
    uint cost;
public:
    explicit Item(uint durability = 10, uint cost = 10) : durability(durability), cost(cost) {};

    bool is_broken() {
        return durability == 0;
    }

    uint get_cost() {
        return cost;
    }

    void reduce_durability(uint d = 1) {
        if (durability > d) {
            durability -= d;
        } else {
            durability = 0;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Item &item) {
        os << "durability = " << item.durability
                  << "; cost = " << item.cost
                  << std::endl;
        return os;
    }
};

class Weapon :
        public Item {
private:
    uint damage;
public:
    explicit Weapon(uint durability = 6, uint cost = 10, uint dmg = 3) : Item(durability, cost), damage(dmg) {};

    uint get_damage() {
        return damage;
    }

    friend std::ostream &operator<<(std::ostream &os, const Weapon &weapon) {
        os << "Weapon:\n"
                  << dynamic_cast<const Item&>(weapon)
                  << "damage = " << weapon.damage
                  << std::endl;
        return os;
    }
};

class Armor :
        public Item {
private:
    uint defense;
public:
    explicit Armor(uint durability = 10, uint cost = 4, uint def = 13) : Item(durability, cost), defense(def) {};

    uint get_defense() {
        return defense;
    }

    friend std::ostream &operator<<(std::ostream &os, const Armor &armor) {
        os << "Armor:\n"
                  << dynamic_cast<const Item&>(armor)
                  << "defense = " << armor.defense
                  << std::endl;
        return os;
    }
};

class Hauberk :
        public Armor {
public:
    explicit Hauberk(uint durability = 50, uint cost = 130, uint def = 23) :
            Armor(durability, cost, def) {};

    friend std::ostream &operator<<(std::ostream &os, const Hauberk &hauberk) {
        os << "Hauberk:\n"
                  << dynamic_cast<const Armor&>(hauberk)
                  << std::endl;
        return os;
    }
};

class Lats :
        public Armor {
public:
    explicit Lats(uint durability = 70, uint cost = 250, uint def = 30) :
            Armor(durability, cost, def) {};

    friend std::ostream &operator<<(std::ostream &os, const Lats &lats) {
        os << "Lats:\n"
                  << dynamic_cast<const Armor&>(lats)
                  << std::endl;
        return os;
    }
};

class Shovel :
        public Weapon {
public:
    explicit Shovel(uint durability = 3, uint cost = 5, uint dmg = 1) :
            Weapon(durability, cost, dmg) {};

    friend std::ostream &operator<<(std::ostream &os, const Shovel &shovel) {
        os << "Shovel:\n"
                  << dynamic_cast<const Weapon&>(shovel)
                  << std::endl;
        return os;
    }
};

class Sword :
        public Weapon {
public:
    explicit Sword(uint durability = 7, uint cost = 30, uint dmg = 5) :
            Weapon(durability, cost, dmg) {};

    friend std::ostream &operator<<(std::ostream &os, const Sword &sword) {
        os << "Sword:\n"
                  << dynamic_cast<const Weapon&>(sword)
                  << std::endl;
        return os;
    }
};

class Bow :
        public Weapon {
public:
    explicit Bow(uint durability = 10, uint cost = 20, uint dmg = 3) :
            Weapon(durability, cost, dmg) {};

    friend std::ostream &operator<<(std::ostream &os, const Bow &bow) {
        os << "Bow:\n"
                  << dynamic_cast<const Weapon&>(bow)
                  << std::endl;
        return os;
    }
};

class Human :
        public Alive {
private:
    uint dexterity,
            strength,
            intelligence;
    Weapon *weapon;
    Armor *armor;
public:
    explicit Human(uint hp = 100, uint dext = 0, uint str = 0, uint intel = 0, Weapon* weapon1 = nullptr, Armor* armor1 = nullptr)
            : Alive(hp), dexterity(dext), strength(str), intelligence(intel), weapon(weapon1), armor(armor1) {};

    void reduce_dexterity(uint dex) {
        if (dexterity > dex) {
            dexterity -= dex;
        } else {
            dexterity = 0;
        }
    }

    void reduce_strength(uint st) {
        if (strength > st) {
            strength -= st;
        } else {
            strength = 0;
        }
    }

    void reduce_intelligence(uint intel) {
        if (intelligence > intel) {
            intelligence -= intel;
        } else {
            intelligence = 0;
        }
    }

    void inreae_dexterity(uint dex) {
        dexterity += dex;
    }

    void inreae_strength(uint st) {
        strength += st;
    }

    void inreae_intelligence(uint intel) {
        intelligence += intel;
    }

    void attack() {
        if (weapon != nullptr) {
            std::cout << "Сaused damage = "
                      << weapon->get_damage()
                      << std::endl;
            weapon->reduce_durability(1);
            if (weapon->is_broken()) {
                weapon = nullptr;
            }
        } else {
            std::cout << "Sorry, I haven't a weapon" << std::endl;
        }
    }

    void defense() {
        if (armor != nullptr) {
            std::cout << "Protected = "
                      << armor->get_defense()
                      << std::endl;
            armor->reduce_durability(5);
            if (armor->is_broken()) {
                armor = nullptr;
            }
        } else {
            std::cout << "Sorry, I haven't a armor" << std::endl;
        }
    }

    void equip_armor(Armor *armor1) {
        armor = armor1;
    }

    void equip_weapon(Weapon *weapon1) {
        weapon = weapon1;
    }

    void remove_armor() {
        armor = nullptr;
    }

    void remove_weapon() {
        weapon = nullptr;
    }

    friend std::ostream &operator<<(std::ostream &os, const Human &h) {
        os << "Human's stats:\n" << dynamic_cast<const Alive&>(h)
                  << "dexterity = " << h.dexterity
                  << "; strength = " << h.strength
                  << "; intelligence = " << h.intelligence
                  << std::endl;
        if (h.weapon != nullptr) {
            os << "Have a " << *h.weapon << std::endl;
        } else {
            os << "Haven't a weapon " << std::endl;
        }
        if (h.armor != nullptr) {
            os << "Have a " << *h.armor << std::endl;
        } else {
            os << "Haven't a armor " << std::endl;
        }
        return os;
    }

};

class Peasant :
        public Human {
public:
    explicit Peasant(uint hp = 20, uint dext = 2, uint str = 5, uint intel = 0, Shovel* shovel = nullptr):
            Human(hp,dext, str, intel, shovel) {};
    friend std::ostream &operator<<(std::ostream &os, const Peasant &peasant) {
        os << "I'm a Peasant: \n" << dynamic_cast<const Human&>(peasant) << std::endl;
        return os;
    }
};
class Archer :
        public Human {
public:
    explicit Archer(uint hp = 100, uint dext = 20, uint str = 6, uint intel = 7, Bow* bow = nullptr, Lats* lats = nullptr):
            Human(hp,dext, str, intel, bow, lats) {};
    friend std::ostream &operator<<(std::ostream &os, const Archer &archer) {
        os << "I'm a Archer: \n" << dynamic_cast<const Human&>(archer) << std::endl;
        return os;
    }
};
class Knight :
        public Human {
public:
    explicit Knight(uint hp = 150, uint dext = 10, uint str = 30, uint intel = 1, Sword* sword = nullptr, Hauberk* hauberk = nullptr):
            Human(hp,dext, str, intel, sword, hauberk) {};
    friend std::ostream &operator<<(std::ostream &os, const Knight &knight) {
        os << "I'm a Knight: \n" << dynamic_cast<const Human&>(knight) << std::endl;
        return os;
    }
};


int main() {
//    Alive a{};
//    Human human{};
//    Human h{};
//    Animal an{};
//    Bow bow(9);
//    Shovel shovel(1);
//    Hauberk hauberk{10};
//    Lats lats{};
//    Peasant peasant{12, 54, 3 ,4, &shovel};
//    Archer archer{12, 54, 3 ,4, &bow, &lats};
//    h.increse_max_hp(100);
//    h.inreae_intelligence(10);
//    std::cout << Pig()
//              << peasant
//              << std::endl;
//    human.equip_armor(&lats);
//    human.equip_weapon(&bow);
//    human.reduce_max_hp(20);
//    human.remove_weapon();
//    for (int i = 0; i < 10; ++i) {
//        human.attack();
//    }

}