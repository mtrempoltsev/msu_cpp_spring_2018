#pragma once
#include<iostream>
#include <string>

// класс одушевленных объектов
class animate
{
protected:
	int health; //у каждого есть здоровье, если оно становится <=0, существо погибает
	void set_health(int q);
	std::string personal_name; 
	void set_personal_name(std::string N_name);
	int damage_without_weapon; //урон без оружия ( у людей может быть ещё за счёт оружия )
	void set_damage_without_weapon(int d);
public:
	animate();
	~animate();
};

// класс неодушевленных
class inanimate
{
protected:
	int weigth; //вес предмета, который занимает место в рюкзаке
	int condition; //100- целый, 0 - сломался
	void set_weigth(int q);
	void change_condition();//после использования предмета его целостность как-то меняется
public:
	inanimate();
	~inanimate();
};

// класс людей
class human: public animate
{
protected:
	bool gender; //0 - женщина, 1 - мужчина
	int age; 
	int full_damage; // полный урон,включая оружие, если оно есть
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
	int weapon_damage; //урон от оружия
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

