#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <string>



class Object
{
protected:
	std::string name;
public:	
	std::string get_name() const;	
	void set_name(const std::string& _name);
};

class Being;


class Thing : public Object
{
protected:
	Being* owner;
	int strength;
public:	
	Being* get_owner() const;
	void set_owner(Being* _owner);
	int get_strength() const;
	void set_strength(int _strength);
};


class Weapon : public Thing
{
protected:
	int damage;
	int accuracy;
public:
	Weapon(int _strength, int _damage, int _accuracy);
	int get_damage() const;
	int get_accuracy() const;
};




class Armor : public Thing
{
public:
	Armor(int _strength, int _protection);
	int get_protection() const;
protected:
	int protection;	
};


class Being : public Object
{
protected:
	int hp;
	int strength;
	int ability;
public:
	int get_hp() const;
	int get_strength() const;
	int get_ability() const;
	void set_hp(int _hp);
	void set_strength(int _strength);
	void set_ability(int _ability);
};


class Human : public Being
{
protected:
	Weapon* weapon;
	Armor* armor;
public:
	Human(int _hp, int _strength, int _ability);
};

class Animal : public Being
{
protected:
	int helplessness;
public:
	Animal(int _helplessness, int _hp, int _strength, int _ability);
	int get_helplessness() const;
};



class Shovel : public Weapon
{
public:
	Shovel(Being* _owner);
};


class Sword : public Weapon
{
public:
	Sword(Being* _owner);
};

class Bow : public Weapon
{
	Bow(Being* _owner);
};


class Hauberk : public Armor
{
public:
	Hauberk(Being* _owner);
};

class Lats : public Armor
{
public:
	Lats(Being* _owner);
};

class Peasant : public Human
{
public:
	Peasant(const std::string& _name);
};

class Archer : public Human
{
public:
	Archer(const std::string& _name);
};

class Knight : public Human
{
public:
	Knight(const std::string& _name);
};

class Pig : public Animal
{
public:
	Pig(const std::string& _name);	
};


#endif HEADER_H
