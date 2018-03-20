//Kononov Sergey BD-11

#include <list> 

class Object{
	private:
		int State;
		const int Cost;
	public:
		int get_State() const{
			return State;
		};
		void set_State(int value){
			State = value;
		};
		int get_Cost() const{
			return State;
		};
		
		Object(int state = 0, int cost = 0): State(state), Cost(cost){};
};

class Clothes: public Object{
	private:
		const int Defence;
	public:
		int get_Defence() const{
			return Defence;
		};
	
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

class Weapon: public Object{
	private:
		const int Damage;
	public:
		int get_Damage() const{
			return Damage;
		};

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

class Active{
	private:
		int Health, Defence, Damage;
	public:
		int get_Health() const{
			return Health;
		};
		
		void set_Health(int value){
			Health = value;
		};
		
		int get_Defence() const{
			return Defence;
		};
		
		void set_Defence(int value){
			Defence = value;
		};
		
		int get_Damage() const{
			return Damage;
		};
		
		void set_Damage(int value){
			Damage = value;
		};

		Active(int health = 0, int defence = 0, int damage = 0):
				Health(health), Defence(defence), Damage(damage){};
};

class Animal: public Active{
		const int Benefit;
	public:
		int get_Benefit() const{
			return Benefit;
		};
		
		Animal(int health = 0, int defence = 0, int damage = 0, int benefit = 0): 
				Benefit(benefit), Active(health, defence, damage){};
};

class Human: public Active{
	public:
		int Victories, Defeats;
		std::list <Weapon *> my_weapon; 
		std::list <Clothes *> my_clothes;
		
		Human(int health = 0, int defence = 0, int damage = 0):
				Victories(0), Defeats(0), Active(health, defence, damage){
			my_weapon.clear();
			my_weapon.push_front(nullptr);
			my_clothes.clear();
			my_clothes.push_front(nullptr);
		};

		~Human(){
			int wp_size = my_weapon.size();
			int cl_size = my_clothes.size();

			for (auto it = my_weapon.begin(); it != my_weapon.end(); ++it)
				if (*it != nullptr)
					delete *it;

			for (auto it = my_clothes.begin(); it != my_clothes.end(); ++it)
				if (*it != nullptr)
					delete *it;
		};
};

class Archer: public Human{
	public:
		Archer(): Human(10, 3, 6){
			Weapon *  bow = new WP_bow();
			Clothes * armour = new CL_armour();
			my_weapon.push_front(bow);
			my_clothes.push_front(armour);
		};
};

class Knight: public Human{
	public:
		Knight(): Human(3, 6, 2){
			Weapon *  sword = new WP_sword();
			Clothes * lats = new CL_lats();
			my_weapon.push_front(sword);
			my_clothes.push_front(lats);
		};
};

class Shepherd: public Human{
	public:
		Shepherd(): Human(4, 7, 2){
			Weapon *  whip = new WP_whip();
			Clothes * shirt = new CL_shirt();
			my_weapon.push_front(whip);
			my_clothes.push_front(shirt);
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
