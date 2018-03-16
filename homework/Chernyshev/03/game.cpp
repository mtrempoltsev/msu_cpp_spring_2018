#include <iostream>


class Thing
{
public:
    Thing(int max_hp_)
            : hp(max_hp_), max_hp(max_hp_)
    {
    }

    void use(int damage)
    {
        hp -= damage;

        if (hp < 0) {
            hp = 0;
        }
        if (hp > max_hp) {
            hp = max_hp;
        }
    }

    bool is_broken() const
    {
        return hp <= 0;
    }

    int get_hp() const
    {
        return hp;
    }

    int get_max_hp() const
    {
        return max_hp;
    }

private:
    int hp;
    int max_hp;
};

class Weapon : public Thing
{
public:
    Weapon(int damage_, int max_hp)
            : Thing(max_hp), damage(damage_)
    {
    }

private:
    int damage;
};

class Shovel : public Weapon
{
public:
    Shovel()
            : Weapon(20, 10)
    {
    }
};

class Sword : public Weapon
{
public:
    Sword()
            : Weapon(100, 50)
    {
    }
};

class Bow : public Weapon
{
public:
    Bow()
            : Weapon(30, 23)
    {
    }
};


class Armour : public Thing
{
public:
    Armour(int max_hp)
            : Thing(max_hp)
    {
    }
};

class Hauberk : public Armour
{
public:
    Hauberk()
            : Armour(30)
    {
    }
};

class Corslet : public Armour
{
public:
    Corslet()
            : Armour(64)
    {
    }
};


class Alive
{
public:
    Alive()
            : hp(max_hp)
    {
    }

    bool is_alive() const
    {
        return hp > 0;
    }

    void change_hp(int dif)
    {
        hp += dif;

        if (hp < 0) {
            hp = 0;
        }
        if (hp > max_hp) {
            hp = max_hp;
        }
    }

    int get_hp() const
    {
        return hp;
    }

    int get_max_hp() const
    {
        return max_hp;
    }

    virtual void speak() const
    {
    }

private:
    int hp;
    const static int max_hp = 100;
};


class Person : public Alive
{
public:
    Person(int age_, int height_)
            : Alive(), age(age_), height(height_)
    {
    }

    void change_weapon(Weapon *w)
    {
        weapon = w;
    }

    void remove_weapon()
    {
        weapon = nullptr;
    }

    Weapon *get_weapon()
    {
        return weapon;
    }

    void change_armour(Armour *a)
    {
        armour = a;
    }

    void remove_armour()
    {
        armour = nullptr;
    }

    Armour *get_armour()
    {
        return armour;
    }

private:
    int age;
    int height;
    Weapon *weapon = nullptr;
    Armour *armour = nullptr;
};

class Peasant : public Person
{
public:
    Peasant(int age, int height, Shovel *shovel)
            : Person(age, height)
    {
        change_weapon(shovel);
    }

    void speak() const override
    {
        std::cout << "I'm so tired and my life sucks!" << std::endl;
    }
};

class Archer : public Person
{
public:
    Archer(int age, int height, Bow *bow)
            : Person(age, height)
    {
        change_weapon(bow);
    }
};

class Knight : public Person
{
public:
    Knight(int age, int height, Sword *sword)
            : Person(age, height)
    {
        change_weapon(sword);
    }
};


class Animal : public Alive
{
public:
    Animal(int weight_)
            : Alive(), weight(weight_)
    {
    }

    void change_weight(int w)
    {
        weight = w;
    }

private:
    int weight;
};

class Pig : public Animal
{
public:
    Pig()
            : Animal(200)
    {
    }

    void speak() const override
    {
        std::cout << "Hrgu-hrgu" << std::endl;
    }
};

class Dog : public Animal
{
public:
    Dog()
            : Animal(30)
    {
    }

    void speak() const override
    {
        std::cout << "Woof-woof" << std::endl;
    }
};


// There are some examples of classes use
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    Shovel sh1;
    Peasant p1(21, 167, &sh1);
    p1.speak();


    Bow b1;
    Archer a1(18, 180, &b1);

    cout << b1.get_hp() << ' ' << b1.get_max_hp() << endl;
    while (!a1.get_weapon()->is_broken()) {
        a1.get_weapon()->use(13);
    }
    cout << a1.get_weapon()->is_broken() << endl;
    cout << b1.get_hp() << ' ' << b1.get_max_hp() << endl;


    Dog d1;
    d1.speak();
    Pig pig1;
    pig1.speak();

    Animal &animal1 = d1;
    animal1.speak();
}
