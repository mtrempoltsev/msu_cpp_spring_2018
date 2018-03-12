#ifndef MODULE_GUARD
#define MODULE_GUARD


#include <stdint.h>

enum weapon_id{SWORD, BOW, SHOVEL};
enum armor_id{NO, LATS, HAUBERK};

class weapon_t {
protected:
    uint32_t damage, strenght_cur, strenght_max, cost;
    weapon_id tipe_id;
    uint32_t id;
public:
    weapon_t(weapon_id _tipe_id, uint32_t _id, uint32_t _damage, uint32_t _strenght_cur,
    uint32_t _strenght_max, uint32_t _cost):
    tipe_id(_tipe_id), id(_id), damage(_damage), strenght_cur(_strenght_cur),
    strenght_max(_strenght_max), cost(_cost) {}
    ~weapon_t() {};
    void repair(uint32_t val) {
        strenght_cur = std::min(strenght_max, strenght_cur + val);
    }
    void hurt(uint32_t val) {
        strenght_cur = (val > strenght_cur) ? 0 : strenght_cur - val;
    }
};
class sword: public weapon_t{
public:
    sword(uint32_t _damage = 0, uint32_t _id = 1, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 0): weapon_t(SWORD, _id, _damage, _strenght_cur, _strenght_max, _cost) {}
    ~sword() {}
};
class bow: public weapon_t{
public:
    bow(uint32_t _damage = 0,uint32_t _id = 2, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 0): weapon_t(BOW, _id, _damage, _strenght_cur, _strenght_max, _cost) {}
    ~bow() {}
};
class shovel: public weapon_t{
public:
    shovel(uint32_t _damage = 0,uint32_t _id = 3, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 0): weapon_t(SHOVEL, _id, _damage, _strenght_cur, _strenght_max, _cost) {}
    ~shovel() {}
};

///////////////////////////////////////////////////////////////////////////////////////////
class armor_t {
protected:
    uint32_t defense, strenght_cur, strenght_max, cost;
    armor_id tipe_id;
    uint32_t id;
public:
    armor_t(armor_id _tipe_id, uint32_t _id, uint32_t _defense, uint32_t _strenght_cur,
    uint32_t _strenght_max, uint32_t _cost):
    tipe_id(_tipe_id), id(_id), defense(_defense), strenght_cur(_strenght_cur),
    strenght_max(_strenght_max), cost(_cost) {}
    ~armor_t() {};
    void repair(uint32_t val) {
        strenght_cur = std::min(strenght_max, strenght_cur + val);
    }
    void hurt(uint32_t val) {
        strenght_cur = (val > strenght_cur) ? 0 : strenght_cur - val;
    }
};
class lats: public armor_t{
public:
    lats(uint32_t _damage = 0, uint32_t _id = 1, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 0): armor_t(LATS, _id, _damage, _strenght_cur, _strenght_max, _cost) {}
    ~lats() {}
};

class hauberk: public armor_t{
public:
    hauberk(uint32_t _damage = 0, uint32_t _id = 2, uint32_t _strenght_cur = 0,
    uint32_t _strenght_max = 10, uint32_t _cost = 0): armor_t(HAUBERK, _id, _damage, _strenght_cur, _strenght_max, _cost) {}
    ~hauberk() {}
};

///////////////////////////////////////////////////////////////////////////////////////////
class human{
protected:
    bool weapon_available, armor_available;
    uint32_t health, exp, level, army_id;
    union {lats* armor_l; hauberk* armor_h;} armor;
    union {sword* weapon_sw; bow* weapon_bw; shovel* weapon_sh;} weapon;
    weapon_id w_tipe_id;
    armor_id a_tipe_id;
public:
    human() {};
    ~human() {};
    void add_exp(uint32_t _exp) {
        exp += _exp;
    }
    void add_army_id(uint32_t _army_id) {
        army_id = _army_id;
    }
    void add_weapon_id(weapon_id _w_id) {
        w_tipe_id = _w_id;
    }
    void add_armor_id(armor_id _a_id) {
        a_tipe_id = _a_id;
    }
    void destroy_weapon() {
        if (weapon_available) {
            switch (w_tipe_id) {
                case SWORD: delete weapon.weapon_sw; break;
                case BOW: delete weapon.weapon_bw; break;
                case SHOVEL: delete weapon.weapon_sh; break;
            }
            weapon_available = false;
        }
    }
    void  destroy_armor() {
        if (armor_available) {
            switch (a_tipe_id) {
                case LATS: delete armor.armor_l; break;
                case HAUBERK: delete armor.armor_h; break;
            }
            armor_available = false;
        }
    }
    void add_weapon(sword *_weapon) {
        if (!weapon_available && _weapon) {
            weapon.weapon_sw = _weapon;
            weapon_available = true;
        }
    }
    void add_weapon(bow *_weapon) {
        if (!weapon_available && _weapon) {
            weapon.weapon_bw = _weapon;
            weapon_available = true;
        }
    }
    void add_weapon(shovel *_weapon) {
        if (!weapon_available && _weapon) {
            weapon.weapon_sh = _weapon;
            weapon_available = true;
        }
    }
    void add_armor(lats *_armor) {
        if (!armor_available && _armor) {
            armor.armor_l = _armor;
            armor_available = true;
        }
    }
    void add_armor(hauberk *_armor) {
        if (!armor_available && _armor) {
            armor.armor_h = _armor;
            armor_available = true;
        }
    }
};

class countryman: public human{
public:
    countryman(uint32_t _army_id, uint32_t _exp, shovel *_weapon) {
        human::add_army_id(army_id);
        human::add_exp(_exp);
        human::add_weapon_id(SHOVEL);
        human::add_armor_id(NO);
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
        human::add_weapon_id(BOW);
        human::add_armor_id(HAUBERK);
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
        human::add_weapon_id(SWORD);
        human::add_armor_id(LATS);
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