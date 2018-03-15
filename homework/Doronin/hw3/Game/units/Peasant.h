//
// Created by roman on 14.03.18.
//

#ifndef GAME_PEASANT_H
#define GAME_PEASANT_H


#include "Unit.h"
#include "../weapons/Fist.h"
#include "../Armor/Shirt.h"

class Peasant: public Unit {
protected:
    Shirt*_armor;
    Fist* _weapon;
    uint _damage;
public:
    Peasant()
    {
        this->_health = 100;
        this->_damage = 5;
        this->_armor = new Shirt();
        this->_weapon = new Fist();
    }
    virtual ~Peasant(){
        delete this->_armor;
        delete this->_weapon;
    }
    uint get_health()
    {
        return this->_health + this->_armor->get_armor();
    }

    virtual void set_health(uint hp)
    {
        if(hp==0)
        {
            std::cout<<"peasant is die"<<std::endl;
            this->_health=hp;
            this->~Peasant();
        }
        else
            this->_health=hp;
    }

    virtual void get_weapon(Fist *w)
    {
        delete this->_weapon;
        this->_weapon = w;
        switch (this->_weapon->get_type())
        {
            case  0: this->_damage=5;
                break;
            case  1: this->_damage=10;
                break;
            default: this->_damage=6;
        }
    }

    void get_armor(Shirt *a)
    {
        delete this->_armor;
        this->_armor=a;
    }

    void attack(Unit* u)
    {
        u->set_health(u->get_health() - this->_damage >= 0 ? u->get_health() - this->_damage : 0);
        if(!this->_weapon->use())
        {
            delete[] this->_weapon;
            this->_weapon = new Fist();
        }
    }
};
#endif //GAME_PEASANT_H
