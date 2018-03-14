#pragma once
#include<iostream>
#include <string>

// класс одушевленных объектов
class animate
{
protected:
	int health; //у каждого есть какое-то здоровье, если оно <= то существо погибает
	void set_health(int q);
	std::string personal_name; 
	void set_personal_name(std::string N_name);
	int damage_without_weapon; //урон существа без оружия ( у людей ещё отдельно может быть урон от оружия )
	void set_damage_without_weapon(int d);
public:
	animate();
	~animate();
};

// класс неодушевленных объектов
class inanimate
{
protected:
	int weigth; //вес предмета, которые он будет занимать в рюкзаке у человека
	int condition; //100- идеальное состояние, 0 - сломан
	void set_weigth(int q);
	void change_condition();//после использования предмета его качество будет меняться
public:
	inanimate();
	~inanimate();
};

// класс людей
class human: public animate
{
protected:
	bool gender; //0-женщина, 1-мужчина
	int age; //возраст может меняться
	int full_damage; // полный урон, учитывающий урон оружия и силу человека
	void set_full_damage(int d);
	void set_gender(bool g);
	void set_age(int a);
public:
	human();
	~human();
};

//класс животных
class animal : public animate
{
public:
	animal();
	~animal();
};

//класс свиней
class pig : public animal
{
public:
	pig();
	~pig();
};


//класс оружия
class weapon : public inanimate
{
protected:
	int weapon_damage; //урон оружия
	void set_weapon_damage(int d);
public:
	weapon();
	~weapon();
};

//класс рыцарей
class knight : public human
{
public:
	knight();
	sword* Sword;
	lats* Lats;
	~knight();
};
//класс лучников
class archer : public human
{
public:
	archer();
	bow* Bow;
	hauberk* Hauberk;
	~archer();
};
//класс крестьян
class peasant : public human
{
public:
	peasant();
	shovel* Shovel;
	~peasant();
};

//класс мечей
class sword :public weapon
{
public:
	sword();
	~sword();
};
//класс луков
class bow :public weapon
{
public:
	bow();
	~bow();
};
//класс лопат
class shovel :public weapon
{
public:
	shovel();
	~shovel();
};

class armor : public inanimate
{
protected:
	int protection;
	void set_protection(int p);
public:
	armor();
	~armor();
};

//латы
class lats : public armor
{
public:
	lats();
	~lats();
};

//кольчуга
class hauberk : public armor
{
public:
	hauberk();
	~hauberk();
};

