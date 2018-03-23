#include <cstdint>

class Armor{
public:
    int16_t Armor_Strength;
    int16_t Toughness;
    int16_t Type;
    virtual void receive_hit(int16_t);

};

class No_Armor : public Armor{
private: 
    int16_t agility;

public:
    No_Armor();
    void receive_hit(int16_t);

};

class Plate_Armor : public Armor{
private:
    int16_t durability;

public:
    Plate_Armor();
    void receive_hit(int16_t);
    
};

class Chain_Mail : public Armor{
private:
    int16_t durability;
    int16_t agility;

public:
    Chain_Mail();
    void receive_hit(int16_t);

};