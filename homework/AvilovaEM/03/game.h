class alive 
{
    private:
    int age;
    public:
    alive(int _age) : age(_age) {}
};

class thing {}; //вещи
class weapon : public thing {}; //оружие
class armour : public thing {}; //броня

class hauberk : public armour {}; //кольчуга
class lats : public armour {}; //латы

class sword : public weapon {}; //меч
class bow : public weapon {}; //лук
class shovel : public weapon {}; //лопата

class animal : public alive {};
class pig : public animal {}; //свинья
class dog : public animal {}; //собака

class people : public alive //человек
{
    weapon weapon; //оружие
    armour armour; //броня
    animal animal; //животное
};

class peasant : public people {}; //холоп
class archer : public people {}; //лучник
class knight : public people {}; //рыцарь

class stuff
{
    private:
    std::string name;
    public:
    stuff(std::string s) : name(s) {}
};
