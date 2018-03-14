#pragma once
#include<iostream>

class Life
{
private:
	double HP;
protected:
	int age;
public:
	Life(double h, int a) :
		HP(h), age(a) {}
	bool Is_alive();
	void damage_hp(double c);
	double get_HP() { return HP; }
	virtual ~Life() {}
};

class Resources
{
private:
	int meat;
	int truffle;
	int milk;
	int egg;
	int wool;
public:
	Resources() :
		meat(0), truffle(0), milk(0), egg(0), wool(0) {}
	void add_meat(int add) { meat += add; }
	void add_truffle(int add) { truffle += add; }
	void add_milk(int add) { milk += add; }
	void add_egg(int add) { egg += add; }
	void add_wool(int add) { wool += add; }
	int get_meat() { return meat; }
	int get_truffle() { return truffle; }
	int get_milk() { return milk; }
	int get_egg() { return egg; }
	int get_wool() { return wool; }
	~Resources() {}
};

class Animals :
	public Life
{
private:
	int used_in_units;
public:
	Animals(double h, int a, int u) :
		Life(h, a),
		used_in_units(u) {}
	void growth();
	int give_meat() {return age * used_in_units;}
	int get_age() { return age; }
	int get_uiu() { return used_in_units; }
	~Animals() {}
};


class Chicken :
	public Animals
{
public:
	Chicken() :
		Animals(5.0, rand() % 4 + 1, rand() % 9 + 1) {}
	int give_egg() { return (rand() % 2); }
	~Chicken() { std::cout << "died Chicken" << std::endl; }
};

class Cow :
	public Animals
{
public:
	Cow() :
		Animals(50.0, rand() % 6 + 1, rand() % 9 + 1) {}
	int give_milk() { return rand() % 3; }
	~Cow() { std::cout << "died Cow" << std::endl; }
};

class Pig :
	public Animals
{
public:
	Pig() :
		Animals(30.0, rand() % 6 + 1, rand() % 9 + 1) {}
	int search_truffle() { return (rand() % 3); }
	~Pig() { std::cout << "died Pig" << std::endl; }
};

class Sheep :
	public Animals
{
public:
	Sheep() :
		Animals(10.0, rand() % 6 + 1, rand() % 9 + 1) {}
	int give_wool() { return rand() % 3; }
	~Sheep() { std::cout << "died Sheep" << std::endl; }
};

class Skill
{
private:
	int power;
	int agility;
	int mentality;
public:
	Skill() :
		power(rand() % 10+1),
		agility(rand() % 10+1),
		mentality(rand() % 10+1) {}
	int get_power() { return power; }
	int get_agility() { return agility; }
	int get_mentality() { return mentality; }
	void up_power(int up);
	void up_agility(int up);
	void up_mentality(int up);
	~Skill() {}
};

class Equipment
{
protected:
	double HP;
public:
	Equipment(double h) :
		HP(h) {}
	bool Is_broken()
	{
		if (HP == 0)
			return false;
		return true;
	}
	void used(double damage)
	{
		HP -= damage;
		if (HP < 0)
			HP = 0;
	}
	double get_HP() { return HP; }
	virtual ~Equipment() {}
};

class Armour :
	public Equipment
{
private:
	double magic_protection;
public:
	Armour(double m, double HP) :
		magic_protection(m),
		Equipment(HP) {}
	~Armour() {}
};

class Lats :
	public Armour
{
public:
	Lats() :
		Armour(100.0, rand() % 20 + 1) {}
	~Lats() {}
};

class Hauberk :
	public Armour
{
public:
	Hauberk() :
		Armour(50.0, rand() % 50 + 1) {}
	~Hauberk() {}
};

class Shirt :
	public Armour
{
public:
	Shirt() :
		Armour(10.0, rand() % 5 + 1) {}
	~Shirt() {}
};


class Weapon :
	public Equipment
{
private:
	double damage;
public:
	Weapon(double d, double HP) :
		damage(d),
		Equipment(HP) {}
	double get_damage() { return damage; }
	~Weapon() {}
};

class Sword :
	public Weapon
{
public:
	Sword() :
		Weapon(rand() % 50 + 1, 50.0) {}
	~Sword() {}
};

class Hoe :
	public Weapon
{
public:
	Hoe() :
		Weapon(rand() % 10 + 1, 100.0) {}
	~Hoe() {}
};

class Bow :
	public Weapon
{
public:
	Bow() :
		Weapon(rand() % 70 + 1, 30.0) {}
	~Bow() {}
};

class Human :
	public Life
{
private:
	Skill skill;
	Weapon *weapon = nullptr;
	Armour *armour = nullptr;
	Resources res;
public:
	Human(double h, int a) :
		Life(h, a) {}
	void growth_human();
	Weapon* get_weapon() { return weapon; }
	Armour* get_armour() { return armour; }
	void give_weapon(Weapon *w) { weapon = w; }
	void give_armour(Armour *a) { armour = a; }
	void weapon_used_on(Human &a);
	void kill_pet(Animals& an);
	void check_cow(Cow& an) {res.add_milk(an.give_milk());}
	void check_sheep(Sheep& an) {res.add_wool(an.give_wool());}
	void check_pig(Pig& an) {res.add_truffle(an.search_truffle());}
	void check_chicken(Chicken& an) {res.add_egg(an.give_egg());}
	void check_weapon() { if (weapon->Is_broken()) weapon = nullptr; }
	void check_armour() { if (armour->Is_broken()) armour = nullptr; }
	Resources get_res() { return res; }
	~Human() {}
};

class Knight :
	public Human
{
public:
	Knight(Sword *s, Lats *l) :
		Human(100.0, rand() % 100 + 1) {
		give_weapon(s);
		give_armour(l);
	}
	~Knight() { std::cout << "I'm died, Knight" << std::endl; }
};

class Farmer :
	public Human
{
public:
	Farmer(Hoe *hoe, Shirt *shirt) :
		Human(100.0, rand() % 100 + 1) {
		give_weapon(hoe);
		give_armour(shirt);
	}
	~Farmer() {
		std::cout << "I'm died, Farmer" << std::endl;
		system("pause");
	}
};

class Bowman :
	public Human
{
public:
	Bowman(Bow *b, Hauberk *h) :
		Human(100.0, rand() % 100 + 1) {
		give_armour(h);
		give_weapon(b);
	}
	~Bowman() { std::cout << "I'm died, Bowman" << std::endl; }
};
