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
	Weapon wp("Sword1", 1, 1, "magic");
	Armor arm("Sword1", 1, "magic");

	// Unit Player1();

	cout << wp.attack_type() << endl;

	Pig pig;

	Peasant peasant;
	Knight knight;
	Archer archer;

	Bow b1("cool bow", 1, 1, "pierce");
	Sword b2("cool sword", 1, 1, "magic");
	Showel b3("cool showel", 1, 1, "pierce");

	Lats l3("cool lats", 1, "pierce");
	Hauberk h3("cool hauberk", 1, "pierce");

	// Player player;

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