#pragma once
#include<iostream>
#include <string>

// класс одушевленных объектов
class animate
{
protected:
	int health; //ó êàæäîãî åñòü êàêîå-òî çäîðîâüå, åñëè îíî <= òî ñóùåñòâî ïîãèáàåò
	void set_health(int q);
	std::string personal_name; 
	void set_personal_name(std::string N_name);
	int damage_without_weapon; //óðîí ñóùåñòâà áåç îðóæèÿ ( ó ëþäåé åù¸ îòäåëüíî ìîæåò áûòü óðîí îò îðóæèÿ )
	void set_damage_without_weapon(int d);
public:
	animate();
	~animate();
};

// êëàññ íåîäóøåâëåííûõ îáúåêòîâ
class inanimate
{
protected:
	int weigth; //âåñ ïðåäìåòà, êîòîðûå îí áóäåò çàíèìàòü â ðþêçàêå ó ÷åëîâåêà
	int condition; //100- èäåàëüíîå ñîñòîÿíèå, 0 - ñëîìàí
	void set_weigth(int q);
	void change_condition();//ïîñëå èñïîëüçîâàíèÿ ïðåäìåòà åãî êà÷åñòâî áóäåò ìåíÿòüñÿ
public:
	inanimate();
	~inanimate();
};

// êëàññ ëþäåé
class human: public animate
{
protected:
	bool gender; //0-æåíùèíà, 1-ìóæ÷èíà
	int age; //âîçðàñò ìîæåò ìåíÿòüñÿ
	int full_damage; // ïîëíûé óðîí, ó÷èòûâàþùèé óðîí îðóæèÿ è ñèëó ÷åëîâåêà
	void set_full_damage(int d);
	void set_gender(bool g);
	void set_age(int a);
public:
	human();
	~human();
};

//êëàññ æèâîòíûõ
class animal : public animate
{
public:
	animal();
	~animal();
};

//êëàññ ñâèíåé
class pig : public animal
{
public:
	pig();
	~pig();
};


//êëàññ îðóæèÿ
class weapon : public inanimate
{
protected:
	int weapon_damage; //óðîí îðóæèÿ
	void set_weapon_damage(int d);
public:
	weapon();
	~weapon();
};

//êëàññ ðûöàðåé
class knight : public human
{
public:
	knight();
	sword* Sword;
	lats* Lats;
	~knight();
};
//êëàññ ëó÷íèêîâ
class archer : public human
{
public:
	archer();
	bow* Bow;
	hauberk* Hauberk;
	~archer();
};
//êëàññ êðåñòüÿí
class peasant : public human
{
public:
	peasant();
	shovel* Shovel;
	~peasant();
};

//êëàññ ìå÷åé
class sword :public weapon
{
public:
	sword();
	~sword();
};
//êëàññ ëóêîâ
class bow :public weapon
{
public:
	bow();
	~bow();
};
//êëàññ ëîïàò
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

//ëàòû
class lats : public armor
{
public:
	lats();
	~lats();
};

//êîëü÷óãà
class hauberk : public armor
{
public:
	hauberk();
	~hauberk();
};

