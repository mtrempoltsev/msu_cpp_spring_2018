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
    Sword(): count_use(20)
    {
        _damage=20;
    }
    bool use()
    {
        if(count_use != 0)
        {
            count_use -= 1;
            return true;
        }
        return false;
    }
};


#endif //GAME_SWORD_H
