#include <string>

class Thing
{
	std::string name;
	unsigned durability;
};

class Weapon : public Thing
{
	unsigned damage;
};

class Bow : public Weapon
{

};

class Shovel : public Weapon
{

};

class Sword : public Weapon
{

};

class Armor : public Thing
{

};

class Mail : public Armor
{

};

class Plate : public Armor
{

};


class Unit
{
	std::string name;
	unsigned HP;
};

/*
Переменные haveWeapon и haveArmor отвечают за корректную работу программы при наличии/отсутствии оружия
Если персонаж будет атаковать, соответствующая функция будет осуществлять проверку на наличие оружия
При атаке персонажа будет проверяться наличие у него брони. Если она есть, снимается ее durability, иначе HP персонажа
*/

class People : public Unit
{
	bool haveWeapon;
	bool haveArmor;
	Armor* armor;
	Weapon* weapon;
};

class Peasant : public People
{
	
};

class Archer : public People
{
	
};

class Knight : public People
{
	
};

class Animal : public Unit
{

};

class Pig : public Animal
{

};