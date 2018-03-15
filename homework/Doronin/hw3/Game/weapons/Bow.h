//
// Created by roman on 14.03.18.
//

#ifndef GAME_BOW_H
#define GAME_BOW_H


#include "Fist.h"

class Bow: public Fist
{
protected:
    uint count_use;
public:
    Bow(): count_use(100){
        type = 3;
    }
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

#endif //GAME_BOW_H
