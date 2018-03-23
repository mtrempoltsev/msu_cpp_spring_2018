//
// Created by roman on 14.03.18.
//

#ifndef GAME_SHIRT_H
#define GAME_SHIRT_H

class Shirt
{
protected:
    uint armor;
    uint count_use;
public:
    Shirt():armor(0), count_use(0){}
    uint get_armor()
    {
        count_use -= 1;
        if(count_use !=0)
        {
            count_use -= 1;
            return armor;
        }
        else
            return 0;
    }
};


#endif //GAME_SHIRT_H
