//
//  main.cpp
//  HW-3-C++
//
//  Created by Сергей Окладников on 18/03/2018.
//  Copyright © 2018 Сергей Окладников. All rights reserved.
//

#include <iostream>

class stuff
{
private:
    std::string name;
public:
    stuff(std::string _name)
    {
        name = _name;
    }
};

class live : public stuff
{
private:
    int hp;
public:
    live(int _hp, std::string _name) : stuff(_name), hp(_hp) {}
};

class thing : public stuff
{
private:
    int power;
public:
    thing(int _power, std::string _name) : stuff(_name), power(_power) {}
};

class sword : public thing //меч
{
private:
    bool special;
public:
    sword(bool _special, int _power, std::string _name) :
        thing(_power, _name), special(_special) {}
};

class bow : public thing //лук
{
private:
    int distance;
public:
    bow(int _dist, int _power, std::string _name) :
        thing(_power, _name), distance(_dist) {}
};

class shovel : public thing //лопата
{
private:
    int length;
public:
    shovel(int _l, int _power, std::string _name) :
        thing(_power, _name), length(_l) {}
};

class people : public live
{
private:
    int max_age;
public:
    people(int age, int _hp, std::string _name) :
        live(_hp, _name), max_age(age) {}
};

class animal : public live
{
private:
    int weight;
public:
    animal(int _w, int _hp, std::string _name) :
        live(_hp, _name), weight(_w) {}
};

class pig : public animal //свинья
{
private:
    int dirty;
public:
    pig(int _dir, int _w, int _hp, std::string _name) :
    animal(_w, _hp, _name), dirty(_dir) {}
};

class dog : public animal //собака
{
private:
    int force;
public:
    dog(int _f, int _w = 100, int _hp = 10, std::string _name = "Jack") :
    animal(_w, _hp, _name), force(_f) {}
};

class peasant : public people //холоп
{
private:
    bool free;
    pig pig;
public:
    peasant(class pig _pig, bool _f, int _age, int _hp, std::string _name) :
        people(_age, _hp, _name), free(_f), pig(_pig) {}
};

class archer : public people //лучник
{
private:
    int skill;
    bow bow;
public:
    archer(class bow _bow, int _s, int _age, int _hp, std::string _name) :
        people(_age, _hp, _name), skill(_s), bow(_bow) {}
};

class knight : public people //рыцарь
{
private:
    int dignity; //достоинство
    sword sword;
public:
    knight(class sword _sword, int _d, int _age, int _hp, std::string _name) :
        people(_age, _hp, _name), dignity(_d), sword(_sword) {}
};

int main()
{
    return 0;
}
