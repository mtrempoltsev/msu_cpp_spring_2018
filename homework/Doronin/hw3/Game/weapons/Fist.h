//
// Created by roman on 14.03.18.
//

#ifndef GAME_FIST_H
#define GAME_FIST_H


class Fist {
protected:
   uint _damage;
public:
    Fist(): _damage(5){}
    virtual ~Fist() = default;
    uint get_damage()
    {
        return _damage;
    }
    virtual bool  use()
    {
        return true;
    }
};

#endif //GAME_FIST_H
