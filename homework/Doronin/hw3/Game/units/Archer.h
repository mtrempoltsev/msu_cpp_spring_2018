//
// Created by roman on 14.03.18.
//

#ifndef GAME_ARCHER_H
#define GAME_ARCHER_H


#include "Peasant.h"

class Archer : public Peasant {
public:
    virtual ~Archer() = default;
    void get_weapon(Fist *w)
    {
        delete this->_weapon;
        this->_weapon=w;
        switch (this->_weapon->get_type())
        {
            case  0: this->_damage=5;
                break;
            case  3: this->_damage=12;
                break;
            default: this->_damage=6;
        }
    }

    void set_health(uint hp)
    {
        if(hp == 0) {
            std::cout<<"archer is die"<<std::endl;
            this->~Archer();
        }
        else
            this->_health=hp;
    }
};
#endif //GAME_ARCHER_H
