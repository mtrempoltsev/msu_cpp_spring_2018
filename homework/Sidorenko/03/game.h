/* some description of RPG game classes
*/

//====================wearpon=============
typedef enum {NONE,SHOVEL, BOW, SWORD} wtype; 
class wearpon
{
private:
	int combat_strength;
	int weight;
	wtype wt;
public:
	wearpon(wtype_t, int _s, int _w): 
		combat_strength(_s), weight(_w), wt(_t) {};
	wearpon():
		wt(NONE), combat_strength(0), weight(0) {};
	int get_strength()
	{ 
		return combat_strength;
	}
	int get_weight()
	{
		return weight;
	}
	void set_strength(int _s)
	{
		combat_strength = _s;
	}
	void set_weight(int _w)
	{
		weight = _w;
	}
	void set_type(wtype _wt)
	{
		wt = _wt;
	}
	wtype get_type()	
	{
		return wt;
	}
};

const wearpon no_wearpon(NONE, 0, 0);

//=================armor===================
typedef enum {NONE, LATS, HAUBERG} armtype;
class armor
{
private:
	int defense;
	int weight;
	armtype at;
public:
	armor(armtype _at, int _d, int _w): 
		defense(_d), weight(_w), at(_at) {};
	int get_defense()
	{ 
		return defense;
	}
	int get_weight()
	{
		return weight;
	}
	void set_defense(int _d)
	{
		defense = _d;
	}
	void set_weight(int _w)
	{
		weight = _w;
	}
	void set_type(armtype _at)
	{
		at = _at;
	}
	armtype get_type()	
	{
		return at;
	}
};

const armor no_armor(NONE, 0, 0);


//================person===============
typedef enum {PEASANT, ARCHER, KNIGHT} ptype;
class person
{
private:
	wearpon w;
	armor a;
	int hp;	
	ptype pt;
public:
	person(ptype _pt, int _hp, 
	       wearpon _w = no_wearpon, armor _a = no_armor):
		pt(_pt), hp(_hp), w(_w), a(_a) {}

	void give_wearpon(wearpon h)
	{
		w = h;
	}
	void give_armor(armor b)
	{
		a = b;
	}
	void crush_wearpon()
	{
		wearpon = no_wearpon;
	}
	void crush_armor()
	{
		armor = no_armor;
	}
	bool armed()
	{
		return a != no_armor;
	}
	bool equipted()
	{
		return w != no_wearpon;
	}
	int get_hp()
	{
		return hp;
	}
	void heal(int h)
	{
		hp += h;
	}
	void damage(int dam)
	{
		hp -= dam;
	}
	bool isdead()
	{
		return (hp <= 0);
	}
};

//==============animal================
class animal
{
protected:
	int hp;
public:
	animal(int _hp): hp(_hp) {};
	int get_hp()
	{
		return hp;
	}
	void heal(int h)
	{
		hp += h;
	}
	void damage(int dam)
	{
		hp -= dam;
	}
	bool isdead()
	{
		return (hp <= 0);
	}
};

typedef enum {WOLF, BEAR} t_comb_animal;
class combat_animal: animal
{
private:
	int combat_strength;
	int defense;
	t_comb_animal type;
	
public:
	combat_animal(t_comb_animal _t, int _c, int _d, int _hp):
		animal(_hp), type(_t), combat_strength(_c), defense(_d)
	void set_defense(int _d)
	{
		defense = _d;
	}
	int get_defense()
	{ 
		return defense;
	}
	int get_strength()
	{
		return combat_strength;
	}
	void set_strength(int _s)
	{
		combat_strength = _s;
	}
	
};

typedef {PIG, CAT} t_home_animal;
class home_animal: animal
{
private:
	t_home_animal type;
public:
	home_animal(t_home_animal _t, int _hp):
		animal(_hp), type(_t) {}
} 

