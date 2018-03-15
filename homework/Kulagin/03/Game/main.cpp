#include <iostream>

#include "include/Weapon.h"
#include "include/Armor.h"

#include "include/Pig.h"

#include "include/Peasant.h"
#include "include/Knight.h"
#include "include/Archer.h"

#include "include/Player.h"


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