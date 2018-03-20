class Item {

	protected:
		std::string name; //имя предмета
		int full_strength; //прочность предмета
		int strength; //текущая прочность предмета
		double weight; //вес предмета
		int cost; //стоимомть предмета

};

class Weapon : Item {

	protected:
		int damage_min, damage_max; //минимальный и максимальный урон
		double distance; //длина аттаки. -1 если оружие ближнего боя
	
	public:
		int hit(){} //возвращает урон нанесенное этим оружием. -1 если промазал 

};

class Sword : Weapon {};
class Two_Handed_Sword : Weapon {};
class Bow : Weapon {};
class Crossbow : Weapon {};
class Pitchfork : Weapon {};
class Rolling_Pin : Weapon {};

class Equipment : Item {

	protected:
		int defend_level;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

};

class Armor : Equipment {};
class Leather_Armor : Equipment {};
class Shirt : Equipment {};

class Living_Creature {

	protected:
		std::string name; //имя существа
		int full_life; //максимальное здоровье
		int life; // текущее здоровье
		double speed; // скорость существа

};

class Animal : Living_Creature {};

class Pig : Animal {
	
	public:
		void heal(); //Лечит героя

};
class Hourse : Animal {

	public:
		void jump(); //Прыгает

};
class Dog : Animal {

	protected:
		int min_damage, max_damage;

	public:
		void hit(Living_Creature creature); //Аттакует выбранное существо

};

class Hero : Living_Creature {

	protected:
		enum Gender
		{
			male,
			female
		};
		Gender gender;
		int min_damage, max_damage;
		std::vector<Item> items;

	public:
		void sell(Item item) {}
		void buy(Item item) {}
		int hit(Weapon weapon) {}
		void switch_weapon() {}
		void unique_ubility() {}
};

class Knight : Hero {

	protected:
		Sword sword;
		Two_Handed_Sword two_handed_sword;
		Hourse hourse;
		Armor armor;
		enum Main_weapon
		{
			sword,
			two_handed_sword;
		};
		Main_weapon main_weapon; //оружие, которое в руках
		
};

class Archer{

	protected:
		Bow bow;
		Crossbow crossbow;
		Dog dog;
		Leather_Armor leather_armor;
		enum Main_weapon
		{
			bow,
			crossbow;
		};
		Main_weapon main_weapon; //оружие, которое в руках

};

class Peasant : Hero {

	protected:
		Pitchfork pitchfork;
		Rolling_Pin rollin_pin;
		Pig pig;
		Shirt shirt;
		enum Main_weapon
		{
			pitchfork,
			rollin_pin;
		};
		Main_weapon main_weapon; //оружие, которое в руках

};
