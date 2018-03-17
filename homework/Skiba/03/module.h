#ifndef MODULE_GUARD
#define MODULE_GUARD


#include <stdint.h>

class Weapon {
protected:
    uint32_t damage, strenght_cur, strenght_max, cost;
    uint32_t id;
public:
    Weapon() {}
    ~Weapon() {};
    void repair(uint32_t val) {
        strenght_cur = std::min(strenght_max, strenght_cur + val);
    }
    void hurt(uint32_t val) {
        strenght_cur = (val > strenght_cur) ? 0 : strenght_cur - val;
    }
};
class sword: public Weapon{
public:
    sword(uint32_t _damage = 0, uint32_t _id = 1, uint32_t _strenght_cur = 10,
    uint32_t _strenght_max = 10, uint32_t _cost = 100) {
        damage = _damage;
        id = _id;
        strenght_cur = _strenght_cur;
        strenght_max = _strenght_max;
        cost = _cost;
    }
    ~sword() {}
};
class bow: public Weapon{
public:
    bow(uint32_t _damage = 0,uint32_t _id = 2, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 50) {
        damage = _damage;
        id = _id;
        strenght_cur = _strenght_cur;
        strenght_max = _strenght_max;
        cost = _cost;
    }
    ~bow() {}
};
class shovel: public Weapon{
public:
    shovel(uint32_t _damage = 0,uint32_t _id = 3, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 10) {
        damage = _damage;
        id = _id;
        strenght_cur = _strenght_cur;
        strenght_max = _strenght_max;
        cost = _cost;
    }
    ~shovel() {}
};

///////////////////////////////////////////////////////////////////////////////////////////
class Armor {
protected:
    uint32_t defense, strenght_cur, strenght_max, cost;
    uint32_t id;
public:
    Armor() {}
    ~Armor() {}
    void repair(uint32_t val) {
        strenght_cur = std::min(strenght_max, strenght_cur + val);
    }
    void hurt(uint32_t val) {
        strenght_cur = (val > strenght_cur) ? 0 : strenght_cur - val;
    }
};
class lats: public Armor{
public:
    lats(uint32_t _defense = 0, uint32_t _id = 1, uint32_t _strenght_cur = 10,
    uint32_t _strenght_max = 10, uint32_t _cost = 200) {
        defense = _defense;
        id = _id;
        strenght_cur = _strenght_cur;
        strenght_max = _strenght_max;
        cost = _cost;
    }
    ~lats() {}
};

class hauberk: public Armor{
public:
    hauberk(uint32_t _defense = 0, uint32_t _id = 2, uint32_t _strenght_cur = 10,
    uint32_t _strenght_max = 10, uint32_t _cost = 150){
        defense = _defense;
        id = _id;
        strenght_cur = _strenght_cur;
        strenght_max = _strenght_max;
        cost = _cost;
    }
    ~hauberk() {}
};

///////////////////////////////////////////////////////////////////////////////////////////
class human{
protected:
    bool weapon_available, armor_available;
    uint32_t health, exp, level, army_id;
    Armor *armor;
    Weapon *weapon;
public:
    human() {};
    ~human() {};
    void add_exp(uint32_t _exp) {
        exp += _exp;
    }
    void add_army_id(uint32_t _army_id) {
        army_id = _army_id;
    }
    void destroy_weapon() {
        if (weapon_available) {
            delete weapon;
            weapon_available = false;
        }
    }
    void  destroy_armor() {
        if (armor_available) {
            delete armor;
            armor_available = false;
        }
    }
    void add_weapon(Weapon *_weapon) {
        if (!weapon_available && _weapon) {
            weapon = _weapon;
            weapon_available = true;
        }
    }
    void add_armor(Armor *_armor) {
        if (!armor_available && _armor) {
            armor = _armor;
            armor_available = true;
        }
    }
};

class countryman: public human{
public:
    countryman(uint32_t _army_id, uint32_t _exp, shovel *_weapon) {
        human::add_army_id(army_id);
        human::add_exp(_exp);
        human::add_weapon(_weapon);
    }
    ~countryman() {
        human::destroy_armor();
        human::destroy_weapon();
    }
    void special_ablity() {
    }
    uint32_t calc_and_get_lvl() {
        level = exp / 100;
        return level;
    }
};

class archer: public human{
public:
    archer(uint32_t _army_id, uint32_t _exp, hauberk *_armor, bow *_weapon) {
        human::add_army_id(army_id);
        human::add_exp(_exp);
        human::add_weapon(_weapon);
        human::add_armor(_armor);
    }
    ~archer() {
        human::destroy_armor();
        human::destroy_weapon();
    }
    void special_ablity() {
    }
    uint32_t calc_and_get_lvl() {
        level = exp / 150;
        return level;
    }
};

class knight: public human{
public:
    knight(uint32_t _army_id, uint32_t _exp, lats *_armor, sword *_weapon) {
        human::add_army_id(army_id);
        human::add_exp(_exp);
        human::add_weapon(_weapon);
        human::add_armor(_armor);
    }
    ~knight() {
        human::destroy_armor();
        human::destroy_weapon();
    }
    void special_ablity() {
    }
    uint32_t calc_and_get_lvl() {
        level = exp / 300;
        return level;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////
class animal{
protected:
    uint32_t health, speed;
public:
    animal(uint32_t _health, uint32_t _speed = 100): health(_health), speed(_speed) {}
    ~animal() {}
};
class pig: public animal{
public:
    pig(uint32_t _health, uint32_t _speed) : animal(_health, _speed) {}
    ~pig() {}
};
class cow: public animal{
public:
    cow(uint32_t _health, uint32_t _speed) : animal(_health, _speed) {}
    ~cow() {}
};
#endif