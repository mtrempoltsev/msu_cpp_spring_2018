#pragma once

#include <string>
#include <memory>

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
	void set_name(const std::string& new_name) { name = new_name; }

protected:

	Point location;
	std::string name;
};


class Item : public Object
{
public:
	
	int get_weight() { return weight; }

	void set_weight(int new_weight) { weight = new_weight; }

protected:

	int weight;
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
};


class Projectile_Weapon : public Weapon
{
public:

	int get_ammo() { return ammo; }

	void set_ammo(int new_ammo) { new_ammo = ammo; }

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
	int get_base_damage() { return base_damage; }

	void set_weapon(Weapon* new_weapon) { weapon = new_weapon; }
	void set_armor(Armor* new_armor) { armor = new_armor; }
	void set_base_damage(int new_base_damage) { base_damage = new_base_damage; }

protected:

	Weapon* weapon;
	Armor* armor;
	int base_damage;
};

class Animal : public Persona
{
public:

	int get_damage() { return damage; }

	void set_damage(int new_damage) { new_damage = damage; }

protected:

	int damage;
};

// Classes for which instances will be created

struct Shovel : public Weapon
{
	Shovel(Human* owner_persona)
	{
		name = "Shovel";
		location = owner_persona->get_location();
		weight = 2;
		strength = 100;
		damage = 10;
		range = 20;

		owner_persona->set_weapon(this);
	}

	Shovel(Point weapon_location)
	{
		name = "Shovel";
		location = weapon_location;
		weight = 2;
		strength = 100;
		damage = 10;
		range = 20;
	}

};


struct Sword : public Weapon
{
	Sword(Human* owner_persona)
	{
		name = "Sword";
		location = owner_persona->get_location();
		weight = 5;
		strength = 300;
		damage = 50;
		range = 10;

		owner_persona->set_weapon(this);
	}

	Sword(Point weapon_location)
	{
		name = "Sword";
		location = weapon_location;
		weight = 5;
		strength = 300;
		damage = 50;
		range = 10;
	}
};

struct Bow : public Projectile_Weapon
{
	Bow(Human* owner_persona)
	{
		name = "Bow";
		location = owner_persona->get_location();
		weight = 5;
		strength = 300;
		damage = 50;
		range = 10;
		ammo = 20;

		owner_persona->set_weapon(this);
	}

	Bow(Point weapon_location)
	{
		name = "Bow";
		location = weapon_location;
		weight = 5;
		strength = 300;
		damage = 50;
		range = 10;
		ammo = 20;
	}
};

struct Plate_armor : public Armor
{
	Plate_armor(Human* owner_persona)
	{
		name = "Plate Armor";
		location = owner_persona->get_location();
		weight = 40;
		strength = 500;
		efficiency = 100;

		owner_persona->set_armor(this);
	}

	Plate_armor(Point armor_location)
	{
		name = "Plate Armor";
		location = armor_location;
		weight = 40;
		strength = 500;
		efficiency = 100;
	}
};

struct Chain_mail : public Armor, std::enable_shared_from_this<Chain_mail>
{
	Chain_mail(Human* owner_persona)
	{
		name = "Chain Mail";
		location = owner_persona->get_location();
		weight = 10;
		strength = 300;
		efficiency = 50;

		owner_persona->set_armor(this);
	}

	Chain_mail(Point armor_location)
	{
		name = "Chain Mail";
		location = armor_location;
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
		armor = nullptr;
		base_damage = 5;
	}

	~Peasant()
	{
		delete weapon;
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
		base_damage = 10;
	}

	~Archer()
	{
		delete weapon;
		delete armor;
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
		base_damage = 15;
	}

	~Knight()
	{
		delete weapon;
		delete armor;
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