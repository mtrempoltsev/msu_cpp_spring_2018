//
// Created by roman on 14.03.18.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H


class Unit {
protected:
    uint _health;

public:
    Unit(): _health(100) {}
    virtual ~Unit()= default;
    virtual uint get_health()
    {
        return this->_health;
    }

    virtual  void set_health(uint hp)
    {
        if(hp == 0)
             this->~Unit();
        else
            this->_health=hp;
    }
};

#endif //GAME_UNIT_H
