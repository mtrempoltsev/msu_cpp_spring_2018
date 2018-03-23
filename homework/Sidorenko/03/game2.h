/* Описание классов РПГ игры
*/

//Описание класса предметов: оружия и брони
class Thing
{
protected:
	Human *owner; //nullptr means thing does not belong to anybody
	std::string name; 
public:	
	Thing(const std::string& _name);
	Human* GetOwner();
	void SetOwner(const Human &h);
	std::string& GetName();
};

class Weapon: public Thing
{
	int attack;
public:
	Weapon(const std::string& _name, int _attack);
	int GetAttack();
	void SetAttack(int _a);
};

class Shovel: public Weapon
{
public:
	Shovel(const std::string& _name, int _attack);
};

class Bow: public Weapon
{
public:
	Bow(const std::string& _name, int _attack);
};

class Sword: public Weapon
{
public:
	Sword(const std::string& _name, int _attack);
};

class Armor: public Thing
{
	int defense;
public:
	Armor(const std::string& _name, int _def);
	int GetDefense();
	void SetDefense(int _d);
};

class Hauberk: public Armor
{
public:
	Hauberk(const std::string& _name, int _def);
};

class Lats: public Armor
{
public:
	Lats(const std::string& _name, int _def);
};

//описание класса живого создания: человека или животного
class Creature
{
protected:
	int health;
	std::string name;
public:
	Creature(const std::string _name, int _health);
	void heal(int _h);
	void damage(int _d);
	bool IsDead();
	int GetHealth();
	std::string& GetName();
};

class Human: public Creature
{
protected:
	Weapon *w; //w == nullptr - нет оружия
	Armor *ar; //ar == nullptr - нет брони
	int hp;
public:
	//create a man without anything
	Human(const std::string name, int _health); 
	void SetWeapon(Weapon *w);
	void SetArmor(Armor *ar);
	Weapon* GetWeapon();
	Armor* GetArmor();
	bool IsEquipped(); 
	bool IsArmored();
	void IncHp(int _gift);
	void DestroyArmor(); //destruct the structure of weapon 
	void DestroyWeapon();
};

class Peasant: public Human
{
public:
	Peasant(const std::string _name, int _health);
};	

class Archer: public Human
{
public:
	Archer(const std::string _name, int _health);
};	

class Knight: public Human
{
public:
	Knight(const std::string _name, int _health);
};	

class Animal
{
protected:
	int attack, defense;
public:
	Animal(const std::string& _name, int health, int _a, int _d);
	int GetAttack();
	int GetDefense();
	void SetAttack(int _a);
	void SetDefense(int _d);
};

class Pig: public Animal
{
public:
	Pig(const std::string& _name, int health, int _a, int _d);
};
	


	 
