#include <iostream>
#include <cstdint>
#include "units/Archer.h"
#include "units/Knight.h"
#include "Armor/Lats.h"
#include "Armor/Hauber.h"
#include "weapons/Bow.h"
#include "weapons/Showel.h"
#include "weapons/Sword.h"
#include "units/Pig.h"


int main() {

    Peasant* f_peasant = new Peasant();
    Knight* f_knight = new Knight();

    Fist* saber1 = new Sword();

    f_knight->get_weapon(saber1);

    for(int i=1; i < 6; i++) {
        std::cout <<"strike"<<i<<" "<<f_peasant->get_health() << std::endl;
        f_knight->attack(f_peasant);
    }

    Archer* f_archer = new Archer();
    Lats* lats = new Lats();
    f_archer->get_armor(lats);
    while(f_archer->get_health() !=0 && f_knight->get_health() != 0)
    {
        f_archer->attack(f_knight);
        f_knight->attack(f_archer);
        std::cout<<"archer hp="<<f_archer->get_health()<<std::endl;
        std::cout<<"knight hp="<<f_knight->get_health()<<std::endl;
    }

    if(f_archer->get_health() != 0)
        std::cout<<"win archer"<<std::endl;
    else
        std::cout<<"win knight"<<std::endl;


    delete f_knight;
    delete f_peasant;
    delete f_archer;


    return 0;
}