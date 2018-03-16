#include <iostream>

#include "include/Animal/Pig.h"

#include "include/Player/Peasant.h"
#include "include/Player/Knight.h"
#include "include/Player/Archer.h"

#include "include/Tool/Weapon/Sword.h"
#include "include/Tool/Weapon/Bow.h"
#include "include/Tool/Weapon/Showel.h"

#include "include/Tool/Armor/Lats.h"
#include "include/Tool/Armor/Hauberk.h"

using namespace std;

int main() {
	// Weapon wp("Sword1", 1, 1, "magic");
	// Armor arm("Sword1", 1, "magic");

	// cout << wp.attack_type() << endl;

	Pig pig;

	Peasant peasant;
	Knight knight;
	Archer archer;

	Bow bow("cool bow", 1, 1, "pierce");
	Sword sword("cool sword", 1, 1, "magic");
	Showel showel("cool showel", 1, 1, "pierce");

	Lats lats("cool lats", 1, "pierce");
	Hauberk hauberk("cool hauberk", 1, "pierce");

	// Tool tool;
	// Sword sw("sd");
	// knight.add_tool(&tool);
	knight.add_tool(&sword);
	knight.add_tool(&lats);

	knight.set_weapon("cool sword");
	knight.set_armor("cool lats");

	knight.print_tools("Tools:");

	// knight.add_tool(&sword);
	// Tool sw("sword");
	// Weapon sword("sword", 1, 1, "d");

	// player.add_tool(&sword);

	// player.print_tools();

	// player.set_weapon("sword");
	// player.set_armor("sword");
	// player.remove_tool(&sword);

	// player.print_tools();

	return 0;
}
