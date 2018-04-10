#include "./characters/Beastmaster.h"
#include "characters/Archer.h"
#include "characters/Swordman.h"
#include "characters/Barbarian.h"

int main() {
    Beastmaster* beastmaster = new Beastmaster();
    Archer* archer = new Archer();
    Swordman* swordman = new Swordman();
    Barbarian* barbarian = new Barbarian();

    beastmaster->useAnimal();
    beastmaster->showInfo();
    archer->showInfo();
    beastmaster->attack(archer);
    std::cout << std::endl;
    beastmaster->showInfo();
    archer->showInfo();
    beastmaster->attack(archer);
    std::cout << std::endl;
    beastmaster->showInfo();
    archer->showInfo();
    return 0;
}