//
// Created by roman on 14.03.18.
//

#ifndef GAME_KNIGHT_H
#define GAME_KNIGHT_H


#include "Unit.h"

class Knight: public Peasant
{
public:
    virtual ~Knight() = default;
    void get_weapon(Fist* w)
    {
        delete this->_weapon;
        this->_weapon=w;
        switch (this->_weapon->get_type())
        {
            case  0: this->_damage=6;
                break;
            case  2: this->_damage=20;
                break;
            default: this->_damage=6;
        }
    }

    void set_health(uint hp)
    {
        if(hp == 0) {
            std::cout<<"knight is die"<<std::endl;
            this->~Knight();
        }
        else
            this->_health=hp;
    }
};


#endif //GAME_KNIGHT_H
