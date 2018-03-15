//
// Created by roman on 14.03.18.
//

#ifndef GAME_SWORD_H
#define GAME_SWORD_H


#include "Fist.h"

class Sword: public Fist
{
protected:
    uint count_use;
public:
    Sword(): count_use(100){
       type = 2;
    }
    ~Sword()= default;
    bool use()
    {
        if(this->count_use != 0)
        {
            this->count_use -= 1;
            return true;
        }
        return false;
    }
};


#endif //GAME_SWORD_H
