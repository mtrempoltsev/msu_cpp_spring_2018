#pragma once
#include <string>



class Item {
protected:
	//Unit* item_owner;
	const std::string name;
	unsigned durability;
	bool is_available = true;// если durability вещи становится ниже некоторого порога, вещь ломается и ее нельзя больше использовать
};

class Unit {
protected:
	Item* owner;
	const std::string name;
	unsigned hp, attack, defense;
};

class Animal
{
protected:
	const std::string name;
	unsigned hp;
};

class Weapon : public Item {
protected:
	unsigned damage;
	unsigned range;
};

////
class Shovel : public Weapon
{

};

class Sword : public Weapon
{

};

class Bow : public Weapon
{

};
////
class Armor : public Item
{

protected:
	unsigned defense;
};

class Hauberk : public Armor
{

};

class Lats : public Armor
{

};
////
class Farmer : public Unit
{
	Shovel* shovel;
};

class Archer : public Unit
{
	Bow* bow;
	Hauberk* hauberk;
};

class Knight : public Unit
{
	Sword* sword;
	Lats* lats;
};


class Pig : public Animal
{

};
