#pragma once
#include<iostream>
#include <string>

// класс одушевленных объектов
class Animate
{
protected:
	int health; //у каждого есть какое-то здоровье, если оно <= то существо погибает
	void set_health(int q);
	std::string personal_name; 
	void set_personal_name(std::string & const N_name);
	int damage_without_weapon; //урон существа без оружия ( у людей ещё отдельно может быть урон от оружия )
	void set_damage_without_weapon(int d);
public:
	Animate();
	~Animate();
};

// класс неодушевленных объектов
class Inanimate
{
protected:
	int weigth; //вес предмета, которые он будет занимать в рюкзаке у человека
	int condition; //100- идеальное состояние, 0 - сломан
	void set_weigth(int q);
	void change_condition();//после использования предмета его качество будет меняться
public:
	Inanimate();
	~Inanimate();
};

//класс оружия
class Weapon : public Inanimate
{
public:
	Weapon();
	~Weapon();
};

//класс мечей
class Sword :public Weapon
{
public:
	Sword();
	~Sword();
};
//класс луков
class Bow :public Weapon
{
public:
	Bow();
	~Bow();
};
//класс лопат
class Shovel :public Weapon
{
public:
	Shovel();
	~Shovel();
};

class Armor : public Inanimate
{
protected:
	int protection;
	void set_protection(int p);
public:
	Armor();
	~Armor();
};

//латы
class Lats : public Armor
{
public:
	Lats();
	~Lats();
};

//кольчуга
class Hauberk : public Armor
{
public:
	Hauberk();
	~Hauberk();
};

// класс людей
class Human: public Animate
{
private:
	bool have_weapon;
	bool have_armor;
	Armor* armor;
	Weapon* weapon;
protected:
	bool gender; //0-женщина, 1-мужчина
	int age; //возраст может меняться
	int full_damage; // полный урон, учитывающий урон оружия и силу человека
	void set_full_damage(int d);
	void set_gender(bool g);
	void set_age(int a);
	void set_weapon();
	void set_armor();
public:
	bool check_weapon();
	bool check_armor();
	Human();
	~Human();
};

//класс животных
class Animal : public Animate
{
public:
	Animal();
	~Animal();
};

//класс свиней
class Pig : public Animal
{
public:
	Pig();
	~Pig();
};


//класс рыцарей
class Knight : public Human
{
public:
	Knight();
	Sword* sword;
	Lats* lats;
	~Knight();
};
//класс лучников
class archer : public Human
{
public:
	archer();
	Bow* bow;
	Hauberk* hauberk;
	~archer();
};
//класс крестьян
class Peasant : public Human
{
public:
	Peasant();
	Shovel* shovel;
	~Peasant();
};


