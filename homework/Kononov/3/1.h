//Kononov Sergey BD.11

#include <list> 

class Object{
	public:
		int State;
		const int Cost;
		
		Object(int state = 0, int cost = 0): State(state), Cost(cost){};
};

class Clothes: public Object{
	public:
		const int Defence;
		
		Clothes(int state = 0, int cost = 0, int defence = 0):
				Defence(defence), Object(state, cost){};
};

class CL_lats: public Clothes{
	public:
		CL_lats(): Clothes(45, 56, 25){};
};

class CL_armour: public Clothes{
	public:
		CL_armour(): Clothes(43, 35, 52){};
};

class CL_shirt: public Clothes{
	public:
		CL_shirt(): Clothes(92, 25, 42){};
};

class CL_none: public Clothes{};

class Weapon: public Object{
	public:
		const int Damage;
		
		Weapon(int state = 0, int cost = 0, int damage = 0): 
				Damage(damage), Object(state, cost){};
};

class WP_bow: public Weapon{
	public:
		WP_bow(): Weapon(83, 32, 85){};
};

class WP_sword: public Weapon{
	public:
		WP_sword(): Weapon(47, 28, 55){};
};

class WP_whip: public Weapon{
	public:
		WP_whip(): Weapon(72, 33, 68){};
};

class WP_none: public Weapon{};

class Active{
	public:
		int Health, Defence, Damage;
		
		Active(int health = 0, int defence = 0, int damage = 0):
				Health(health), Defence(defence), Damage(damage){};
};

class Animal: public Active{
	public:
		int Benefit;
		
		Animal(int health = 0, int defence = 0, int damage = 0, int benefit = 0): 
				Benefit(benefit), Active(health, defence, damage){};
};

class Human: public Active{
	public:
		int Victories, Defeats;
		std::list <Weapon> my_weapon; 
		std::list <Clothes> my_clothes;
		
		Human(int health = 0, int defence = 0, int damage = 0):
				Victories(0), Defeats(0), Active(health, defence, damage){
			my_weapon.clear();
			my_weapon.push_front(WP_none());
			my_clothes.clear();
			my_clothes.push_front(CL_none());
		};
};

class Archer: public Human{
	public:
		Archer(): Human(10, 3, 6){
			my_weapon.push_front(WP_bow());
			my_clothes.push_front(CL_armour());
		};
};

class Knight: public Human{
	public:
		Knight(): Human(3, 6, 2){
			my_weapon.push_front(WP_sword());
			my_clothes.push_front(CL_lats());
		};
};

class Shepherd: public Human{
	public:
		Shepherd(): Human(4, 7, 2){
			my_weapon.push_front(WP_whip());
			my_clothes.push_front(CL_shirt());
		};
};

class Pig: public Animal{
	public:
		Pig(): Animal(10 ,9 ,8, 6){};
};

class Dog: public Animal{
	public:
		Dog(): Animal(6, 8, 10, 3){};
};

class Horse: public Animal{
	public:
		Horse(): Animal(7, 9, 10, 6){};
};
