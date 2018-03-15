#include<iostream>
#include<time.h>
#include "03_Header.h"

std::string Object::get_name() const
{
	return name;
}

void Object::set_name(const std::string& _name)
{
	name = _name; 
}

Being* Thing::get_owner() const
{
	return owner;
}

void Thing::set_owner(Being* _owner)
{
	owner = _owner;
}

int Thing::get_strength() const
{
	return strength;
}

void Thing::set_strength(int _strength)
{
	strength = _strength;
}

Weapon::Weapon(int _strength, int _damage, int _accuracy)
{
	damage = _damage;
	accuracy = _accuracy;
	strength = _strength;
}

int Weapon::get_damage() const
{
	return damage;
}

int Weapon::get_accuracy() const
{
	return accuracy;
}

Shovel::Shovel(Being* _owner):Weapon(100,10,10)
{
	name = "Shovel" + (rand() % 99 + 1);		
	owner = _owner;				
}

Sword::Sword(Being* _owner):Weapon(200, 30, 10)
{
	name = "Sword" + (rand() % 99 + 1);
	owner = _owner;
}

Bow::Bow(Being* _owner):Weapon(200, 30, 100)
{
	name = "Bow" + (rand() % 99 + 1);
	owner = _owner;
}

Armor::Armor(int _strength, int _protection)
{
	strength = _strength;
	protection = _protection;
}

int Armor::get_protection() const
{
	return protection;
}

Hauberk::Hauberk(Being* _owner):Armor(100, 50)
{
	name = "Hauberk" + (rand() % 99 + 1);
	owner = _owner;
}

Lats::Lats(Being* _owner):Armor(200, 70)
{
	name = "Lats" + (rand() % 99 + 1);
	owner = _owner;
}

int Being::get_hp() const
{
	return hp;
}

int Being::get_strength() const
{
	return strength;
}

int Being::get_ability() const
{
	return ability;
}

void Being::set_hp(int _hp)
{
	hp = _hp;
}


void Being::set_strength(int _strength)
{
	strength = _strength;
}


void Being::set_ability(int _ability)
{
	ability = _ability;
}

Animal::Animal(int _helplessness, int _hp, int _strength, int _ability)
{
	helplessness = _helplessness;
	hp = _hp;
	strength = _strength;
	ability = _ability;
}

int Animal::get_helplessness() const
{
	return helplessness;
}

Human::Human(int _hp, int _strength, int _ability)
{
	hp = _hp;
	strength = _strength;
	ability = _ability;
}

Peasant::Peasant(const std::string& _name):Human(100, 10, 10)
{
	name = _name;
	weapon = new Shovel(this);    //например, так
	armor = NULL;
}

Archer::Archer(const std::string& _name):Human(100, 50, 60)
{
	name = _name;
	weapon = new Bow(this);
	armor = new Hauberk(this);
}

Knight::Knight(const std::string& _name) :Human(100, 50, 50)
{
	name = _name;
	weapon = new Sword(this);
	armor = new Lats(this);
}

Pig::Pig(const std::string& _name):Animal(80, 100, 10, 5)
{
	name = _name;
}

int main()
{
	srand(time(NULL));
	return 0;
}

