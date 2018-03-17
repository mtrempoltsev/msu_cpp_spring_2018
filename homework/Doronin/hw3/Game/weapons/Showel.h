//
// Created by roman on 14.03.18.
//

#ifndef GAME_SHOWEL_H
#define GAME_SHOWEL_H


#include "Fist.h"

class Showel: public Fist
{
private:
    uint count_use;
public:
    Showel(): count_use(20)
    {
        _damage = 8;
    }
    bool use()
    {
        if(this->count_use != 0)
        {
            this->count_use -= 1;
            return true;
        }
        return true;
    }
};


#endif //GAME_SHOWEL_H
