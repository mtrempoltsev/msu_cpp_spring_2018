//check my kaka-game
#include <iostream>
#include "Game.h"

int main()
{
	Hoe h1;
	Shirt s1;
	Farmer f1(&h1, &s1);
	Pig p1;
	Bow b1;
	Hauberk ha1;
	Bowman a1(&b1, &ha1);
	Sword sw1;
	Lats l1;
	Knight k1(&sw1, &l1);
	int i = 0;
	while (f1.Is_alive() && a1.Is_alive()){
		std::cout << f1.get_HP() << std::endl;
		std::cout << a1.get_HP() << std::endl;
		f1.weapon_used_on(a1);
		i++;	}
	std::cout << f1.get_HP() << std::endl;
	std::cout << a1.get_HP() << std::endl;
	std::cout << i << std::endl;
	return 0;
}
