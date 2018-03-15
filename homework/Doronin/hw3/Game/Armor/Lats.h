//
// Created by roman on 14.03.18.
//

#ifndef GAME_LATS_H
#define GAME_LATS_H


#include "Shirt.h"

class Lats: public Shirt
{
private:
    const uint armor = 5;
    uint count_use;
public:
    Lats(): count_use(10){}
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


#endif //GAME_LATS_H
