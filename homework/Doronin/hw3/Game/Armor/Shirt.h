//
// Created by roman on 14.03.18.
//

#ifndef GAME_SHIRT_H
#define GAME_SHIRT_H

class Shirt
{
private:
    const uint armor = 0;
public:
    virtual uint get_armor()
    {
        return this->armor;
    }
};


#endif //GAME_SHIRT_H
