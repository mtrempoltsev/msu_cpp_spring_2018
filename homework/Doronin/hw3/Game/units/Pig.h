//
// Created by roman on 14.03.18.
//

#ifndef GAME_PIG_H
#define GAME_PIG_H


#include "Unit.h"

class Pig: public Unit {
public:
    Pig(){
        _health = 50;
    }

    void set_health(uint hp)
    {
        if(hp == 0) {
            std::cout << "pig death" << std::endl;
            _health=0;
        }
        else
            _health=hp;
    }

    void make_hry()
    {
        std::cout<<"hry"<<std::endl;
    }
};


#endif //GAME_PIG_H
