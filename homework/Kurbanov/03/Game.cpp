#include "Game.h"



bool Life::Is_alive()
{
	if (HP == 0)
	{
		//душа покинула бренное тело
		std::cout << "Kill me, please. I don't have HP" << std::endl;
		return false;
	}
	return true;
}

void Life::damage_hp(double c)
{
	HP -= c;
	if (HP < 0)
		HP = 0;
}

void Animals::growth()
{
	age++;
	if (age > 10)
		//надо убить, Hz как сделать грамотно
		return;
}

void Skill::up_mentality(int up) {
	mentality += up;
	if (mentality > 10)
		mentality = 10;
}

void Skill::up_agility(int up) {
	agility += up;
	if (agility > 10)
		agility = 10;
}

void Skill::up_power(int up) {
	power += up;
	if (power > 10)
		power = 10;
}

void Human::growth_human()
{
	age++;
	if (age > 100)
		//надо убить, Hz как сделать...
		return;
}

void Human::weapon_used_on(Human& a)
{
	if (weapon == nullptr || a.weapon == nullptr)
	{
		//кулачный бой
		a.damage_hp(skill.get_mentality()*skill.get_power()*skill.get_agility() / (1000.));
		damage_hp(a.skill.get_mentality()*a.skill.get_agility()*a.skill.get_power() / (1000.));
		skill.up_agility(rand() % 2);
		skill.up_mentality(rand() % 2);
		skill.up_power(rand() % 2);
		return;
	}
	if (armour == nullptr || a.armour == nullptr)
	{
		//бой без брони
		weapon->used(rand() % 100);
		a.weapon->used(rand() % 100);
		a.damage_hp((weapon->get_damage() * skill.get_power() * skill.get_mentality() * skill.get_power()) / (1000.));
		damage_hp((a.weapon->get_damage() * a.skill.get_agility() * a.skill.get_mentality() * a.skill.get_agility()) / (1000. ));
		a.check_weapon();
		check_weapon();
		skill.up_agility(rand() % 3);
		skill.up_mentality(rand() % 3);
		skill.up_power(rand() % 3);
		return;
	}
	a.damage_hp((weapon->get_damage() * skill.get_power() * skill.get_mentality() * skill.get_power()) / (1000.*a.armour->get_HP()));
	damage_hp((a.weapon->get_damage() * a.skill.get_agility() * a.skill.get_mentality() * a.skill.get_agility()) / (100. * armour->get_HP()));
	weapon->used(rand() % 100);
	a.weapon->used(rand() % 100);
	armour->used(a.weapon->get_damage());
	a.armour->used(weapon->get_damage());
	a.check_armour();
	a.check_weapon();
	check_armour();
	check_weapon();
	skill.up_agility(rand() % 4);
	skill.up_mentality(rand() % 4);
	skill.up_power(rand() % 4);
}

void Human::kill_pet(Animals& an) 
{
	res.add_meat(an.give_meat());
	an.damage_hp(100.);
	an.Is_alive();
}
