#include "Items.h"

void Human::set_weapon(Weapon *new_weapon){
	weapon = new_weapon;
	weapon->set_owner(this);
}

void Human::set_armorequipment(Armorequipment *new_armorequipment){
	armorequipment = new_armorequipment;
	armorequipment->set_owner(this);
}
 