#include <string>

class Weapon
{
	std::string name;
	unsigned durability;
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

class Armor
{
	std::string name;
	unsigned durability;
};

class Mail : public Armor
{

};

class Plate : public Armor
{

};

/*
	Переменные haveWeapon и haveArmor отвечают за корректную работу программы при наличии/отсутствии оружия
	Если персонаж будет атаковать, соответствующая функция будет осуществлять проверку на наличие оружия
	При атаке персонажа будет проверяться наличие у него брони. Если она есть, снимается ее durability, иначе HP персонажа
*/

class Unit
{
	std::string name;
	unsigned HP;
	bool haveWeapon;
	bool haveArmor;
	Armor* armor;
};

class Peasant : public Unit
{
	Shovel* shovel;
};

class Archer : public Unit
{
	Bow* bow;
};

class Knight : public Unit
{
	Sword* sword;
};

class Animal
{
	std::string name;
	unsigned HP;
};

class Pig : public Animal
{

};