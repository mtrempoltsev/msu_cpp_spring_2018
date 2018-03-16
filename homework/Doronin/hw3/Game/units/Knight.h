//
// Created by roman on 14.03.18.
//

#ifndef GAME_KNIGHT_H
#define GAME_KNIGHT_H


#include "Unit.h"

class Knight: public Peasant
{
public:
    void set_health(uint hp)
    {
        if(hp == 0) {
            std::cout<<"knight is die"<<std::endl;
            _health = 0;
        }
        else
            _health=hp;
    }
};


#endif //GAME_KNIGHT_H
