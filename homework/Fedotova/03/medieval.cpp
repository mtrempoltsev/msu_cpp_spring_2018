#include "medieval.h"

const unsigned Farmer::farmer_hp = 100;
const unsigned Farmer::farmer_attack = 100;
const unsigned Farmer::farmer_defense = 100;
const unsigned Knight::knight_hp = 100;
const unsigned Knight::knight_attack = 100;
const unsigned Knight::knight_defense = 100;
const unsigned Archer::archer_hp = 100;
const unsigned Archer::archer_attack = 100;
const unsigned Archer::archer_defense = 100;
const unsigned Pig::pig_hp = 100;
const unsigned Pig::pig_attack = 100;
const unsigned Pig::pig_defense = 100;

Alive::Alive(const std::string & name, unsigned hp, unsigned attack, unsigned defense): name(name), hp(hp), attack(attack), defense(defense) {}

void Thing::Destroy(unsigned br) {
    brokenness += br;
    if (brokenness >= firmness)
        broken = true;
        // some printf
}

Thing::Thing(const std::string & name, unsigned firm): name(name), firmness(firm), brokenness(0), owner(nullptr), broken(false) {}

Thing::~Thing() {}

void Thing::SetOwner(Human * ptr) {
    owner = ptr;
}

Human * Thing::GetOwner() const {
    return owner;
}

void Thing::RemoveOwner() {
    owner = nullptr;
}

Arsenal::Arsenal(const std::string & name, unsigned firm, unsigned attack): Thing(name, firm), attack(attack) {}

Arsenal::~Arsenal() {
    if (GetOwner())
        GetOwner()->ars = nullptr;
}

Armor::Armor(const std::string & name, unsigned firm, unsigned defense): Thing(name, firm), defense(defense) {}

Armor::~Armor() {
    if (GetOwner())
        GetOwner()->arm = nullptr;
}

std::string Shovel::NameOfClass() const {
    return std::string("Shovel");
}

std::string Sword::NameOfClass() const {
    return std::string("Sword");
}

std::string Arch::NameOfClass() const {
    return std::string("Arch");
}

std::string Lats::NameOfClass() const {
    return std::string("Lats");
}

std::string Chain::NameOfClass() const {
    return std::string("Chain");
}

Human::Human(const std::string & name, bool gender, unsigned hp, unsigned attack, unsigned defense, const std::set<std::string> & arsenals, const std::set<std::string> & armors): Alive(name, hp, attack, defense), gender(gender), ars(nullptr), arm(nullptr), exp(0), arsenals(arsenals), armors(armors) {}

Human::~Human() {
    if (ars)
        ars->owner = nullptr;
    if (arm)
        arm->owner = nullptr;
}

void Human::TakeArsenal(Arsenal * pars) {
    if (arsenals.find(std::string(pars->NameOfClass())) != arsenals.end() && pars->owner == nullptr && ars == nullptr) {
        ars = pars;
        pars->owner = this;
        // some printf
    }
    //else
        // some printf
}

void Human::TakeArmor(Armor * parm) {
    if (armors.find(std::string(parm->NameOfClass())) != armors.end() && parm->owner == nullptr && arm == nullptr) {
        arm = parm;
        parm->owner = this;
        // some printf
    }
    //else
        // some printf
}

void Human::RemoveArsenal() {
    if (ars) {
        ars->RemoveOwner();
        ars = nullptr;
    }
}


void Human::RemoveArmor() {
    if (arm) {
        arm->RemoveOwner();
        arm = nullptr;
    }
}

Farmer::Farmer(const std::string & name, bool gender): Human(name, gender, farmer_hp, farmer_attack, farmer_defense, std::set<std::string>({std::string("Shovel")}), std::set<std::string>()) {}

Knight::Knight(const std::string & name, bool gender): Human(name, gender, knight_hp, knight_attack, knight_defense, std::set<std::string>({std::string("Sword")}), std::set<std::string>({std::string("Lats")})) {}

Archer::Archer(const std::string & name, bool gender): Human(name, gender, archer_hp, archer_attack, archer_defense, std::set<std::string>({std::string("Arch")}), std::set<std::string>({std::string("Chain")})) {}

Animal::Animal(const std::string & name, unsigned hp, unsigned attack, unsigned defense): Alive(name, hp, attack, defense) {}

Animal::~Animal() {}

Pig::Pig(const std::string & name, bool gender): Animal(name, pig_hp, pig_attack, pig_defense) {}

void Battle(Alive * comp1, Alive * comp2) {
    /* some actions with destroying of arsenals and armors
    
    в этой функции должен определиться исход боя и действие боя на участников; для расчета урона и тому подобного необходимо знать атаку, защиту, hp для участников и их оружий и доспехов; кроме того, функция должна уметь добавлять людям опыт и поломанность предметам, а такие методы, очевидно, публичными делать не надо - поэтому пришлось (рассуждая таким образом) сделать эту функцию ко всему подряд дружественной
    
    функция не описана конкретно, поскольку мне неочевидно, как именно должен проходить бой
    
    короче говоря, я считаю, что функция Battle - очень особенная, и ей как раз про всё знать надо
    */
}
