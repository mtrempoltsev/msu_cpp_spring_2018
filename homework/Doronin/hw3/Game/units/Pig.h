//
// Created by roman on 14.03.18.
//

#ifndef GAME_PIG_H
#define GAME_PIG_H


#include "Unit.h"

class Pig: public Unit {
protected:
    uint _health;

public:
    Pig(): _health(50) {}

    virtual uint get_health()
    {
        return this->_health;
    }

    virtual  void set_health(uint hp)
    {
        if(hp == 0)
            this->~Pig();
        else
            this->_health=hp;
    }

    void make_hry()
    {
        std::cout<<"hry"<<std::endl;
    }
};


#endif //GAME_PIG_H
