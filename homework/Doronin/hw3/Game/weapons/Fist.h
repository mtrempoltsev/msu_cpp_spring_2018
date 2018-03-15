//
// Created by roman on 14.03.18.
//

#ifndef GAME_FIST_H
#define GAME_FIST_H


class Fist {
protected:
   uint type;

public:
    Fist(): type(0){}
    virtual uint get_type()
    {
        return this->type;
    }

    virtual bool  use()
    {
        return true;
    }
};


#endif //GAME_FIST_H
