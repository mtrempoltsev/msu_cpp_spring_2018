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
public:
    Peasant():_armor(new Shirt()), _weapon(new Fist())
    {
        _health = 100;
    }
    virtual ~Peasant(){
        delete _armor;
        delete _weapon;
    }
    uint get_health()
    {
        return _health > 0 ? _health + _armor->get_armor() : 0;
    }

    virtual void set_health(uint hp)
    {
        if(hp==0)
        {
            std::cout<<"peasant is die"<<std::endl;
            _health=0;
        }
        else
            _health=hp;
    }

    void get_weapon(Fist *w)
    {
        delete _weapon;
        _weapon = w;
    }

    void get_armor(Shirt *a)
    {
        delete _armor;
        _armor=a;
    }

    void attack(Unit* u)
    {
        u->set_health(u->get_health() - _weapon->get_damage() >= 0 ? u->get_health() - _weapon->get_damage() : 0);
        if(!_weapon->use())
        {
            delete _weapon;
            _weapon = new Fist();
        }
    }
};
#endif //GAME_PEASANT_H
