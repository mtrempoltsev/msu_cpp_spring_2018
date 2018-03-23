//
// Created by roman on 14.03.18.
//

#ifndef GAME_HAUBER_H
#define GAME_HAUBER_H


#include "Shirt.h"

class Hauber : public Shirt
{
public:
    Hauber()
    {
        count_use = 10;
        armor = 4;
    }

};

#endif //GAME_HAUBER_H
