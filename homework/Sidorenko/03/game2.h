/* Описание классов РПГ игры
*/

//Описание класса предметов: оружия и брони
class Thing
{
protected:
	Human *owner; //nullptr means thing does not belong to anybody
	std::string name; 
public:	
	thing(std::string& _name);
	Human* GetOwner();
	friend void Human::SetWearpon(Wearpon *w);
	friend void Human::SetArmor(Armor *ar);
	std::string& GetName();
};

class Wearpon: public Thing
{
	int attack;
public:
	Wearpon(std::string& _name, int _attack);
	int GetAttack();
	void SetAttack(int _a);
};

class Shovel: public Wearpon
{
public:
	Shovel(std::string& _name, int _attack);
	std::string& GetType(); //выдаёт тип оружия (здесь: Shovel)
};

class Bow: public Wearpon
{
public:
	Bow(std::string& _name, int _attack);
	std::string& GetType();
};

class Sword: public Wearpon
{
public:
	Sword(std::string& _name, int _attack);
	std::string& GetType();
};

class Armor: public Thing
{
	int defense;
public:
	Wearpon(std::string& _name, int _def);
	int GetDefense();
	void SetDefense(int _d);
};

class Hauberk: public Armor
{
public:
	Hauberk(std::string& _name, int _def);
	std::string& GetType(); //выдаёт тип брони (здесь Hauberk)
};

class Lats: public Armor
{
public:
	Lats(std::string& _name, int _def);
	std::string& GetType();
};

//описание класса живого создания: человека или животного
class Creature
{
protected:
	int health;
	std::string name;
public:
	Creature(std::string _name, int _health);
	void heal(int _h);
	void damage(int _d);
	bool IsDead();
	int GetHealth();
	std::string& GetName();
};

class Human: public Creature
{
protected:
	Wearpon *w; //w == nullptr - нет оружия
	Armor *ar; //ar == nullptr - нет брони
	int hp;
public:
	//create a man without anything
	Human(std::string name, int _health); 
	void SetWearpon(Wearpon *w);
	void SetArmor(Armor *ar);
	Wearpon* GetWearpon();
	Armor* GetArmor();
	bool IsEquipped(); 
	bool IsArmored();
	void IncHp(int _gift);
	void DestroyArmor(); //destruct the structure of wearpon 
	void DestroyWearpon();
};

class Peasant: public Human
{
public:
	Peasant(std::string _name, int _health);
	std::string& GetType(); //выдаёт сословие (здесь: Peasant)
};	
class Archer: public Human
{
public:
	Archer(std::string _name, int _health);
	std::string& GetType();
};	
class Knight: public Human
{
public:
	Knight(std::string _name, int _health);
	std::string& GetType();
};	

class Animal
{
protected:
	int attack, defense;
public:
	Animal(std::string& _name, int health, int _a, int _d);
	int GetAttack();
	int GetDefense();
	void SetAttack(int _a);
	void SetDefense(int _d);
};

class Pig: public Animal
{
public:
	Pig(std::string& _name, int health, int _a, int _d);
	std::string& GetType();
}
	


	 
