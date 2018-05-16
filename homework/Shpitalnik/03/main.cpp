
class Item{
    unsigned durability;
};

class Weapon: public Item{
    unsigned damage;
};

class Sword: public Weapon{
};

class Bow: public Weapon{
};

class Shovel: public Weapon{
};

class Armor: public Item{
    unsigned defence;
};

class Lats: public Armor{
};

class Hauberk: public Armor{
};

class Unit{
    int x_coord;
    int y_coord;
    unsigned hp;
};

class Animal: public Unit{
};

class Pig: public Animal{
};

class Human: public Unit{
    Armor *armor_ = NULL;
    Weapon *weapon_ = NULL;
};

class Knight: public Human{
};

class Arcer: public Human{
};

class Farmer: public Human{
};
