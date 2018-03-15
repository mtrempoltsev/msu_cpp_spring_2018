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
    virtual uint get_health()
    {
        return _health;
    }

    virtual  void set_health(uint hp)
    {
        if(hp == 0)
             std::cout<<"unit death"<<std::endl;
        else
            _health=hp;
    }
};

#endif //GAME_UNIT_H
