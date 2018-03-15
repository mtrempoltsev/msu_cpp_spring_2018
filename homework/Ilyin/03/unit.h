#include <utility>
#include "weapon.h"
#include "armor.h"

class Unit{
private:
    int16_t hp;

protected:
    Armor armor_equip;
    Weapon weapon_equip;
    float speed;
    int16_t strength;

public:
    std::pair<float, float> position;
    void move(std::pair<float, float>);
    void receive_damage(Weapon, int16_t);

    virtual void broken_weapon();
    virtual int16_t make_hit(std::pair<float, float>);
};

class Archer : public Unit{
private:
    int16_t accuracy;

public:
    Archer(Weapon, Armor, std::pair<float, float>);
    void broken_weapon();
    void escape();

    int16_t make_hit(std::pair<float, float>);

};

class Knight : public Unit{
private:
    int16_t stamina;

public:
    Knight(Weapon, Armor, std::pair<float, float>);
    void broken_weapon();
    int16_t make_hit(std::pair<float, float>);

};

class Peasant : public Unit{
private:
    int16_t skill_penalty;
    int16_t morale;

public:
    Peasant(Weapon, Armor, std::pair<float, float>);
    void broken_weapon();
    void escape();
    int16_t make_hit(std::pair<float, float>);

};

class Piggie : public Unit{
private:
    int16_t morale;

public:
    Piggie(std::pair<float, float>);
    void broken_weapon() {};
    int16_t make_hit(std::pair<float, float>);

};
