#pragma once

#include <string>

struct Point
{
	int x;
	int y;
};


class Object
{
public:

	Point get_location() { return location; }
	std::string get_name() { return name; }

	void set_location(Point new_location) { location = new_location; }
	void set_name(std::string new_name) { name = new_name; }

protected:

	Point location;
	std::string name;
};


class Item : public Object
{
public:

	int get_weight() { return weight; }
	Persona* get_owner() { return owner; }

	void set_weight(int new_weight) { weight = new_weight; }
	void set_owner(Persona* new_owner) { owner = new_owner; }

protected:

	int weight;
	Persona* owner;
};

class Equipment_items : public Item
{
public:

	int get_strength() { return strength; }

	void set_strength(int new_strength) { strength = new_strength; }

protected:
	
	bool able_to_destroyed = true;
	int strength;
};

class Weapon : public Equipment_items
{
public:

	int get_damage() { return damage; }
	int get_range() { return range; }

	void set_damage(int new_damage) { damage = new_damage; }
	void set_range(int new_range) { range = new_range; }

protected:

	int damage;
	int range;
	int strength;
};


class Projectile_Weapon : public Weapon
{
	int get_ammo() { return ammo; }

	int set_ammo(int new_ammo) { new_ammo = ammo; }

protected:

	int ammo;
};


class Armor : public Equipment_items
{
public:

	int get_efficiency() { return efficiency; }

	void set_efficiency(int new_efficiency) { efficiency = new_efficiency; }

protected:

	int efficiency;
};


class Persona : public Object
{
public:

	int get_attitude() { return attitude; }
	int get_hp() {return hp;}
	int get_speed() { return speed; }

	void set_attitude(int new_attitude) { attitude = new_attitude; }
	void set_hp(int new_hp) { hp = new_hp; }
	void set_speed(int new_speed) { speed = new_speed; }

protected:

	int hp;
	int speed;
	int attitude;
};


class Human : public Persona
{
public:
	
	Weapon* get_weapon() { return weapon; }
	Armor* get_armor() { return armor; }
	
	void set_weapon(Weapon* new_weapon) { weapon = new_weapon; }
	void set_armor(Armor* new_armor) { armor = new_armor; }

protected:

	Weapon* weapon;
	Armor* armor;
};

class Animal : public Persona
{
public:

	int get_damage() { return damage; }

	void set_damage(int new_damage) { new_damage = damage; }

protected:

	int damage;
};

//  лассы, дл€ которых будут создаватьс€ экземпл€ры

struct None_weapon : public Weapon
{
	None_weapon(Persona* owner_persona)
	{
		name = "None";
		location = owner_persona->get_location();

		weight = 0;
		owner = owner_persona;

		able_to_destroyed = false;
		strength = 100;

		damage = 5;
		range = 5;
	}
};


struct Shovel : public Weapon
{
	Shovel(Persona* owner_persona)
	{
		name = "Shovel";
		location = owner_persona->get_location();
		weight = 2;
		owner = owner_persona;
		strength = 100;
		damage = 10;
		range = 20;
	}

	Shovel(Point weapon_location)
	{
		name = "Shovel";
		location = weapon_location;
		weight = 2;
		owner = nullptr;
		strength = 100;
		damage = 10;
		range = 20;
	}

};


struct Sword : public Weapon
{
	Sword(Persona* owner_persona)
	{
		name = "Sword";
		location = owner_persona->get_location();
		weight = 5;
		owner = owner_persona;
		strength = 300;
		damage = 50;
		range = 10;
	}

	Sword(Point weapon_location)
	{
		name = "Sword";
		location = weapon_location;
		weight = 5;
		owner = nullptr;
		strength = 300;
		damage = 50;
		range = 10;
	}
};

struct Bow : public Projectile_Weapon
{
	Bow(Persona* owner_persona)
	{
		name = "Bow";
		location = owner_persona->get_location();
		weight = 5;
		owner = owner_persona;
		strength = 300;
		damage = 50;
		range = 10;
		ammo = 20;
	}

	Bow(Point weapon_location)
	{
		name = "Bow";
		location = weapon_location;
		weight = 5;
		owner = nullptr;
		strength = 300;
		damage = 50;
		range = 10;
		ammo = 20;
	}
};

struct None_armor : public Armor
{
	None_armor(Persona* owner_persona)
	{
		name = "None";
		location = owner_persona->get_location();
		weight = 0;
		owner = owner_persona;
		able_to_destroyed = false;
		strength = 100;
		efficiency = 0;
	}
};

struct Plate_armor : public Armor
{
	Plate_armor(Persona* owner_persona)
	{
		name = "Plate Armor";
		location = owner_persona->get_location();
		weight = 40;
		owner = owner_persona;
		strength = 500;
		efficiency = 100;
	}

	Plate_armor(Point armor_location)
	{
		name = "Plate Armor";
		location = armor_location;
		weight = 40;
		owner = nullptr;
		strength = 500;
		efficiency = 100;
	}
};

struct Chain_mail : public Armor
{
	Chain_mail(Persona* owner_persona)
	{
		name = "Chain Mail";
		location = owner_persona->get_location();
		weight = 10;
		owner = owner_persona;
		strength = 300;
		efficiency = 50;
	}

	Chain_mail(Point armor_location)
	{
		name = "Chain Mail";
		location = armor_location;
		weight = 10;
		owner = nullptr;
		strength = 300;
		efficiency = 50;
	}
};

struct Peasant : public Human
{
	Peasant(Point human_location)
	{
		name = "Peasant";
		location = human_location;
		hp = 30;
		speed = 20;
		attitude = 100;
		weapon = new Shovel(this);
		armor = new None_armor(this);
	}
};

struct Archer : public Human
{
	Archer(Point human_location)
	{
		name = "Archer";
		location = human_location;
		hp = 40;
		speed = 25;
		attitude = 50;
		weapon = new Bow(this);
		armor = new Chain_mail(this);
	}
};

struct Knight : public Human
{
	Knight(Point human_location)
	{
		name = "Knight";
		location = human_location;
		hp = 70;
		speed = 10;
		attitude = 40;
		weapon = new Sword(this);
		armor = new Plate_armor(this);
	}
};

struct Pig : public Animal
{
	Pig(Point animal_location)
	{
		name = "Pig";
		location = animal_location;
		hp = 10;
		speed = 25;
		attitude = 70;
		damage = 10;
	}
};