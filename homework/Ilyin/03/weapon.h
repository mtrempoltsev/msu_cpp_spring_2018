#include <cstdint>

class Weapon{
public:
    int16_t Strength;
    int16_t Armor_penetration;
    int16_t Type;
    virtual bool durability_test(int16_t);

};

class Fists : public Weapon{
public:
    Fists();

};

class Bow : public Weapon{
private:
    int16_t durability;
    int16_t ammunition;

public:
    Bow();
    bool durability_test(int16_t);

};

class Sword : public Weapon{
private:
    int16_t durability;

public:
    Sword();
    bool durability_test(int16_t);

};