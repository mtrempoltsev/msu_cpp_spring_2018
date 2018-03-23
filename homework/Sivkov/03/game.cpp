#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <random>


//battleground
namespace bg {
    using hp_t = int;
    enum pig_state {
        NORMAL, BURNING, BACON, NOT_EXIST
    };
    enum body_parts {
        LEGS, HANDS, TORSO, HEAD
    };
    const int BODY_PARTS_SIZE = 4;
    enum weapon_type {
        NOTHING, SWORD, CLUB, BOW, SLING, RAMBO_MACHINE_GUN
    };
    const int WEAPON_TYPE_SIZE = 6;
    enum race_t {
        ORC, ELF
    };

    class Race {
    public:
        explicit Race(race_t race) : race(race) {};

        hp_t attack(hp_t base) {
            switch (race) {
                case ORC:
                    return hp_t(base * 1.2);
                case ELF:
                    return hp_t(base * 0.8);
            }

        }

        hp_t damage(hp_t base) {
            switch (race) {
                case ORC:
                    return hp_t(base * 1.2);
                case ELF:
                    return hp_t(base * 0.8);
            }
        }

        bool is_suitable(weapon_type weapon) {
            switch (race) {
                case ORC:
                    return weapon == CLUB || weapon == SWORD || weapon == RAMBO_MACHINE_GUN;
                case ELF:
                    return weapon == BOW || weapon == SLING || weapon == RAMBO_MACHINE_GUN;
            }
        }

    private:
        race_t race;
    };

    class Pig {
    public:
        Pig() : state(NORMAL) {}

        void Freedom(bool set_fire) {
            if (state == NORMAL && set_fire)
                state = BURNING;
            else if (state == BURNING)
                state = BACON;
            else
                state = NOT_EXIST;
            caught = false;
        }

        pig_state get_state() const {
            pig_state state_tmp = state;
            return state_tmp;
        }

        bool caught = false;
    private:
        pig_state state;
    };

    class Body {
    public:
        Body() = default;

        explicit Body(double stepness_coefficient) {
            body_data = {
                    int(15 * stepness_coefficient),
                    int(15 * stepness_coefficient),
                    int(30 * stepness_coefficient),
                    int(10 * stepness_coefficient)

            };
            step_coefficient = stepness_coefficient;
        }

        void heal() {
            body_data = {
                    int(15 * step_coefficient),
                    int(15 * step_coefficient),
                    int(30 * step_coefficient),
                    int(10 * step_coefficient)
            };
        }

        hp_t damage(hp_t damage_, body_parts part) {
            body_data[part] -= damage_;
            if (body_data[part] < 0)
                body_data[part] = 0;
            return body_data[part];

        }

        std::string to_str(body_parts part) {
            switch (part) {
                case LEGS:
                    return "legs";
                case HANDS:
                    return "hands";
                case TORSO:
                    return "torso";
                case HEAD:
                    return "head";
            }
        }

    private:
        std::vector<hp_t> body_data;
        double step_coefficient = 1.0;
    };

    class Armor {
    public:
        Armor() = default;

        void set_armor(body_parts setter) {
            switch (setter) {
                case LEGS:
                    legs_count = 3;
                    legs = true;
                    break;
                case HANDS:
                    hands_count = 3;
                    hands = true;
                    break;
                case TORSO:
                    torso_count = 3;
                    torso = true;
                    break;
                case HEAD:
                    head_count = 3;
                    head = true;
                    break;
            }
        }

        bool is_armored(body_parts getter) {
            switch (getter) {
                case LEGS: {
                    if (legs)
                        legs_count -= 1;
                    bool legs_tmp = legs;
                    if (legs_count == 0 && legs) {
                        legs = false;
                        std::cout << "legs armor broken" << std::endl;
                    }
                    return legs_tmp;
                }
                case HANDS: {
                    if (hands)
                        hands_count -= 1;
                    bool hands_tmp = hands;
                    if (hands_count == 0 && hands) {
                        hands = false;
                        std::cout << "hands armor broken" << std::endl;
                    }
                    return hands_tmp;
                }
                case TORSO: {
                    if (torso)
                        torso_count -= 1;
                    bool torso_tmp = torso;
                    if (torso_count == 0 && torso) {
                        torso = false;
                        std::cout << "torso armor broken" << std::endl;
                    }
                    return torso_tmp;
                }
                case HEAD: {
                    if (head)
                        head_count -= 1;
                    bool head_tmp = head;
                    if (head_count == 0 && head) {
                        head = false;
                        std::cout << "head armor broken" << std::endl;
                    }
                    return head_tmp;
                }
            }
        }

    private:
        bool legs = false;
        bool hands = false;
        bool torso = false;
        bool head = false;
        int legs_count = 0;
        int hands_count = 0;
        int torso_count = 0;
        int head_count = 0;
    };

    class Weapon {
    public:
        Weapon() = default;

        void set_weapon(weapon_type setter) {
            weapon = setter;
            counter = 3;
        }

        hp_t get_attack() {
            switch (weapon) {
                case SWORD:
                    return 10;
                case CLUB:
                    return 5;
                case BOW:
                    return 10;
                case SLING:
                    return 5;
                case RAMBO_MACHINE_GUN:
                    return 1000;
                case NOTHING:
                    return 2;
            }
            counter -= 1;
            if (counter == 0) {
                std::cout << to_str() << " broken" << std::endl;
                weapon = NOTHING;
            }
        }

        std::string to_str() const {
            switch (weapon) {
                case NOTHING:
                    return "nothing";
                case CLUB:
                    return "club";
                case SWORD:
                    return "sword";
                case SLING:
                    return "sling";
                case BOW:
                    return "bow";
                case RAMBO_MACHINE_GUN:
                    return "RAMBO MACHINE GUN";
            }
        }

    private:
        weapon_type weapon = NOTHING;
        int counter = 0;
    };

    class Fighter {
    public:
        Fighter(double stepness_coefficient, bool SetArsonist,
                std::vector<Pig> *pig_heap,
                std::list<body_parts> *armor_stack,
                std::list<weapon_type> *weapon_stack,
                Race race
        ) :
                pig_heap(pig_heap),
                armor_stack(armor_stack),
                weapon_stack(weapon_stack),
                race(race) {

            body = Body(stepness_coefficient);
            IsPigArsonist = SetArsonist;
        }

        void get_weapon() {
            if (attack_modifier == 0.0)
                std::cout << "ghost" << std::endl;
            else {
                if (!weapon_stack->empty()) {
                    weapon_type weapon_tmp = weapon_stack->back();
                    weapon_stack->pop_back();
                    if (race.is_suitable(weapon_tmp)) {
                        weapon.set_weapon(weapon_tmp);
                        std::cout << weapon.to_str() << " got" << std::endl;
                    } else
                        std::cout << "not suitable" << std::endl;
                } else
                    std::cout << "no more weapons" << std::endl;

            }
        }

        void get_some_armor() {
            if (attack_modifier == 0.0)
                std::cout << "ghost" << std::endl;
            else {
                if (!armor_stack->empty()) {
                    body_parts armor_tmp = armor_stack->back();
                    armor_stack->pop_back();
                    armor.set_armor(armor_tmp);
                    std::cout << body.to_str(armor_tmp) << " armor got" << std::endl;
                } else
                    std::cout << "no more armors" << std::endl;

            }
        }

        void get_pig() {
            if (attack_modifier == 0.0)
                std::cout << "ghost" << std::endl;
            else {
                unsigned long pig_index = rand() % pig_heap->size();
                if (!pig_heap->operator[](pig_index).caught) {
                    switch (pig_heap->operator[](pig_index).get_state()) {
                        case BURNING:
                            PansBurn = true;
                            pig->Freedom(false);
                            std::cout << "your pans are burning" << std::endl;
                            break;
                        case NORMAL:
                            pig = &pig_heap->operator[](pig_index);
                            pig_heap->operator[](pig_index).caught = true;
                            std::cout << "success" << std::endl;
                            break;
                        case BACON:
                            body.heal();
                            pig->Freedom(false);
                            std::cout << "good bacon" << std::endl;
                            break;
                        case NOT_EXIST:
                            std::cout << "not existing pig" << std::endl;
                            break;
                    }
                } else
                    std::cout << "that pig is already caught" << std::endl;
            }
        }


        void attack(Fighter &aim) {
            if (attack_modifier == 0.0)
                std::cout << "ghost" << std::endl;
            else if (std::addressof(aim) == this) {
                std::cout << "you can't attack yourself" << std::endl;
            } else {
                aim.get_damage(race.attack(hp_t(weapon.get_attack() * attack_modifier)));
            }
        }

        void get_damage(hp_t damage) {

            damage = race.damage(damage);

            auto part = body_parts(rand() % 6);

            if (PansBurn)
                damage = damage * 2;

            if (pig != nullptr)
                damage = damage / 2;

            if (armor.is_armored(part))
                damage = damage / 2;

            hp_t reminder = body.damage(damage, part);
            if (reminder == 0) {
                if (part == HEAD || part == TORSO) {
                    attack_modifier = 0.0;
                    std::cout << " he is ghost" << std::endl;
                } else if (part == HANDS || part == LEGS)
                    attack_modifier -= 0.4;
            }

            if (pig != nullptr) {
                pig->Freedom(IsPigArsonist);
                pig = nullptr;
            }

            if (PansBurn)
                PansBurn = false;
            if (reminder > 0)
                std::cout << body.to_str(part) << " damaged " << reminder << " HP remind" << std::endl;
            else
                std::cout << body.to_str(part) << " destroyed" << std::endl;
        }

    private:
        Body body;
        Pig *pig = nullptr;
        Armor armor;
        Weapon weapon;
        bool IsPigArsonist;
        bool PansBurn = false;
        double attack_modifier = 1.0;
        std::vector<Pig> *pig_heap;
        std::list<body_parts> *armor_stack;
        std::list<weapon_type> *weapon_stack;
        Race race;
    };

    void gen_pigs(std::vector<Pig> *base, unsigned int n) {
        base->reserve(n);
        for (unsigned int i = 0; i < n; ++i)
            base->emplace_back(Pig());
    }

    void gen_weapons(std::list<weapon_type> *base, unsigned int n) {
        for (unsigned int i = 0; i < n; ++i) {
            if (rand() % 100 > 95) {
                base->push_back(RAMBO_MACHINE_GUN);
            } else {
                base->push_back(weapon_type(rand() % (WEAPON_TYPE_SIZE - 2) + 1));
            }
        }
    }

    void gen_armor(std::list<body_parts> *base, unsigned int n) {
        for (unsigned int i = 0; i < n; ++i)
            base->push_back(body_parts(rand() % BODY_PARTS_SIZE));
    }

}

void start_game() {
    std::cout << "Enter number of players" << std::endl;
    unsigned int n;
    std::cin >> n;

    std::list<bg::body_parts> armor;
    std::list<bg::weapon_type> weapon;
    std::vector<bg::Pig> pigs;
    bg::gen_armor(&armor, n * 4);
    bg::gen_weapons(&weapon, n);
    bg::gen_pigs(&pigs, n);

    std::vector<bg::Fighter> guys;
    guys.reserve(n);
    for (int p = 0; p < n; ++p) {
        std::cout << "Player " << p << ", are you a pig arsonist? (y/n)" << std::endl;
        char y_n;
        std::cin >> y_n;
        std::cout << "Player " << p << " Do you want stepness 1.0 or random stepness from 0.5 to 1.5? (1 / 2)"
                  << std::endl;
        int type;
        std::cin >> type;
        double stepness;
        bool arsonist = false;
        if (y_n)
            arsonist = true;
        if (type == 1)
            stepness = 1.0;
        else {
            stepness = (rand() % 100) / 100.0 + 0.5;
            std::cout << stepness << std::endl;
        }
        std::cout << "Player " << p << " You are Orc/Elf? (1/2)" << std::endl;
        std::cin >> type;
        if (type == 1)
            guys.emplace_back(bg::Fighter(stepness, arsonist, &pigs, &armor, &weapon, bg::Race(bg::ORC)));
        else
            guys.emplace_back(bg::Fighter(stepness, arsonist, &pigs, &armor, &weapon, bg::Race(bg::ELF)));
    }
    for (int i = 0; i < 20; ++i) {
        for (int p = 0; p < n; ++p) {
            std::cout << "Player " << p
                      << " action? (a - attack, w - get_weapon, r - get armor (!), p - get pig, s - skip)" << std::endl;
            char act;
            std::cin >> act;
            switch (act) {
                case ('a'):
                    std::cout << "Enter player numb" << std::endl;
                    unsigned int numb;
                    std::cin >> numb;
                    guys[p].attack(guys[numb]);
                    break;
                case ('w'):
                    guys[p].get_weapon();
                    break;
                case ('r'):
                    guys[p].get_some_armor();
                    break;
                case ('p'):
                    guys[p].get_pig();
                    break;
                case ('s'):
                    continue;
                default:
                    break;
            }
        }
    }
}


int main() {
    std::cout << "Welcome to my game, enter:\n"
              << "r if you want read rules,\n"
              << "s if you want to start game\n";
    char action;
    std::cin >> action;
    switch (int(action)) {
        case ('r'):
            std::cout << "There are n fighters on arena and n pigs\n"
                      << "n weapons and 4 * n armors.\n"
                      << "Every step you can take weapon, take armor,\n"
                      << "try to get pig or attack another player\n"
                      << "pig could be in 4 states: normal, burning, bacon, not_exist,\n"
                      << "at the beginning all pigs are normal, and you can try to take some pig\n"
                      << "pig reduces damage by 2 times for 1 time you are attacked\n"
                      << "if you are Pig Arsonist you will fire pig after attack\n"
                      << "if you try to catch burning pig, your pans will fire, and pig will bacon\n"
                      << "    if your pans are firing, damage to you is twice multiplied for 1 attack\n"
                      << "if you catch bacon, you will be full healed\n"
                      << "damage is randomly aimed to hand_1, hand_2, leg_1, leg_2, torso or head\n"
                      << "if your body part is armored, damage reduces by 2 times\n"
                      << "if your torso or head are destroyed, you are ghost, and can't do anything\n"
                      << "if your leg or hand destroyed, your attack decrease \n"
                      << "in new version two races: orcs and elfs were added \n";
        case ('s'):
            start_game();
        default:
            std::cout << "exit" << std::endl;
    }
    return 0;
}

