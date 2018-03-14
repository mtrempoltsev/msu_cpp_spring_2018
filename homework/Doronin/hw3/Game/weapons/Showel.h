//
// Created by roman on 14.03.18.
//

#ifndef GAME_SHOWEL_H
#define GAME_SHOWEL_H


#include "Fist.h"

class Showel: public Fist
{
private:
    const uint type = 1;
    uint count_use = 100;
public:
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
