#pragma once

class Weapon;
class Armorequipment;

struct Point{
	int x;
	int y;
};

class Object{
public:
	Point get_location(){
		return location;
	}

	int get_id(){
		return id;
	}

	void set_location(Point new_location){
		location = new_location;
	}

	void set_id(int new_id){
		id = new_id;
	}

protected:
	Point location;
	int id;
};

class Thing : public Object{
public:
	int get_resource(){
		return resource;
	}

	void set_resource(int new_resource){
		resource = new_resource;
	}

protected:
	int resource;
};

class Alive : public Object{
public:
	int get_health(){
		return health;
	}

	void set_health(int new_health){
		health = new_health;
	}

protected:
	int health;
};

class Animal : public Alive{
public:
	int get_quality(){
		return quality;
	}

	void set_quality(int new_quality){
		quality = new_quality;
	}

protected:
	int quality;
};

class Human : public Alive{
public:
	int get_speed(){
		return speed;
	}

	void set_speed(int new_speed){
		speed = new_speed;
	}

	int get_damage(){
		return damage;
	}
	
	void set_damage(int new_damage){
		damage = new_damage;
	}

	int get_type(){
		return type;
	}
	
	void set_type(int new_type){
		type = new_type;
	}

	Weapon* get_weapon(){
		return weapon;
	}

	void set_weapon(Weapon *new_weapon);


	Armorequipment* get_armorequipment(){
		return armorequipment;
	}

	void set_armorequipment(Armorequipment *new_armorequipment);


protected:
	int speed;
	int damage;
	int type;
	Weapon *weapon;
	Armorequipment *armorequipment;
};

class Equipment : public Thing{
public:
	int get_weight(){
		return weight;
	}

	void set_weight(int new_weight){
		weight = new_weight;
	}

	double get_quality(){
		return quality;
	}

	Human* get_owner(){
		return owner;
	}

	void set_owner(Human *new_owner){
		owner = new_owner;
		location = owner->get_location();
	}

protected:
	int weight;
	int quality;
	Human *owner;
};

class Armorequipment : public Equipment{};

class Weapon : public Equipment{
public:
	int get_damage(){
		return damage;
	}

	int get_type(){
		return type;
	}

protected:
	int damage;
	int type;
};

/*------------------------------------------*/

class Pig : public Animal{
public:
	Pig(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		health = 50;
		quality = 50;
	}

	~Pig(){}
};

class Farmer : public Human{
public:
	Farmer(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		health = 50;
		speed = 50;
		type = 0;
	}

	~Farmer(){}
};

class Archer : public Human{
public:
	Archer(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		health = 100;
		speed = 100;
		type = 1;
	}

	~Archer(){}
};

class Knight : public Human{
public:
	Knight(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		health = 200;
		speed = 30;
		type = 2;
	}

	~Knight(){}
};

class Shovel : public Weapon{
public:
	Shovel(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		resource = 10;
		weight = 10;
		quality = 10;
		damage = 10;
		type = 0;
	}

	~Shovel() {}
};

class Arch : public Weapon{
public:
	Arch(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		resource = 10;
		weight = 10;
		quality = 20;
		damage = 30;
		type = 1;
	}

	~Arch() {}
};

class Sword : public Weapon{
public:
	Sword(Point new_location, int new_id){
		location = new_location;
		id = new_id;
		resource = 10;
		weight = 40;
		quality = 30;
		damage = 30;
		type = 2;
	}

	~Sword() {}
};



class Hauberk : public Armorequipment{
public:
	Hauberk(Point new_location, int new_id){
		resource = 100;
		weight = 50;
		quality = 2;
		id = new_id;
		location = new_location;
	}

	~Hauberk(){
	}
};

class Armor : public Armorequipment{
public:
	Armor(Point new_location, int new_id){
		resource = 200;
		weight = 100;
		quality = 3;
		id = new_id;
		location = new_location;
	}

	~Armor(){
	}
};
