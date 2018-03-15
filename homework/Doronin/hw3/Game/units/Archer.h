//
// Created by roman on 14.03.18.
//

#ifndef GAME_ARCHER_H
#define GAME_ARCHER_H


#include "Peasant.h"

class Archer : public Peasant {
public:
    void set_health(uint hp)
    {
        if(hp == 0) {
            std::cout<<"archer is die"<<std::endl;
            _health=0;
        }
        else
            _health=hp;
    }
};
#endif //GAME_ARCHER_H
