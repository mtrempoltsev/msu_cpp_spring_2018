#include <iostream>

class object {
    std::pair<int, int> position;
public:
    object(int x = 0, int y = 0) : position(x, y) {
    }
    std::pair<int, int> get_position() {
        return position;
    }
};

class living_thing {
    int hp;
protected:
    living_thing(int health = 100) : hp(health){
    }
};

class pig : public living_thing {
public:
    pig(int health = 16000) : living_thing(health) {}
};

class weapon {
    int damage;
protected:
    weapon(int dmg) : damage(dmg) {}
public:
    int get_damage() {
        return damage;
    }
};

class melee_weapon : public weapon {
protected:
    melee_weapon(int dmg) : weapon(dmg) {}
};

class ranged_weapon  : public weapon {
    int range;
protected:
    ranged_weapon(int dmg, int rng) : weapon(dmg), range(rng) {}
public:
    int get_range() {
        return range;
    }
};

class bow : public ranged_weapon {
public:
    bow() :  ranged_weapon(10, 5) {}
};

class sword : public melee_weapon {
public:
    sword() : melee_weapon(15) {}
};

class pitchfork : public melee_weapon {
public:
    pitchfork() : melee_weapon(7) {}
};

class clothes {
    int protection;
protected:
    clothes(int def) : protection(def) {}
public:
    int get_protection() {
        return protection;
    }
};

class usual_clothes : public clothes {
    int style;
public:
    usual_clothes(int style) : clothes(2), style(style) {}
};

class light_armor : public clothes {
public:
    light_armor(int def = 5) : clothes(def) {}
};

class heavy_armor : public clothes {
public:
    heavy_armor(int def = 8) : clothes(def) {}
};

enum sex{
    MALE,
    FEMALE
};

class human : public living_thing {
    sex s;
    bool has_weapon = false;
    weapon * wpn;
    clothes * clth;
protected:
    human(int hp, sex s, weapon * wpn, clothes * clothes1) : living_thing(hp), s(s), wpn(wpn), clth(clothes1) {
        if(wpn != nullptr) {
            has_weapon = true;
        }
    }
public:
    ~human() {
        if(wpn != nullptr) delete wpn;
        if(clth != nullptr) delete clth;
    }
};

class peasant : public human {
public:
    peasant(int hp = 100, sex s = MALE, usual_clothes * clothes1 = new usual_clothes(3),  weapon * wpn = nullptr) : human(hp, s, wpn, clothes1) {}
};

class warrior : public human {
protected:
    warrior(int hp, sex s, clothes * clothes1, weapon * wpn) : human(hp, s, wpn, clothes1) {}
};

class swordsman : public warrior {
public:
    swordsman(int hp = 120, sex s = MALE, clothes * clothes1 = new heavy_armor(), melee_weapon * wpn = new sword()) :
            warrior(hp, s, clothes1, wpn) {}
};

class bowman : public warrior {
public:
    bowman(int hp = 100, sex s = MALE, clothes * clothes1 = new light_armor(), ranged_weapon * wpn = new bow()) :
            warrior(hp, s, clothes1, wpn) {}
};