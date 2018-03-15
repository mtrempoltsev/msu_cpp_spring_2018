//
// Created by roman on 14.03.18.
//

#ifndef GAME_HAUBER_H
#define GAME_HAUBER_H


#include "Shirt.h"

class Hauber : public Shirt
{
protected:
    const uint armor = 4;
    uint count_use;
public:
    Hauber(): count_use(10){}
    uint get_armor()
    {
        count_use -= 1;
        if(count_use !=0)
        {
            count_use -= 1;
            return this->armor;
        }
        else
            return 0;
    }
};

#endif //GAME_HAUBER_H
