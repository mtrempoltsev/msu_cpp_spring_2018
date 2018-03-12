#include "medieval.h"

const unsigned Farmer::farmer_hp = 100;
const unsigned Farmer::farmer_atk = 100;
const unsigned Farmer::farmer_dfn = 100;
const unsigned Knight::knight_hp = 100;
const unsigned Knight::knight_atk = 100;
const unsigned Knight::knight_dfn = 100;
const unsigned Archer::archer_hp = 100;
const unsigned Archer::archer_atk = 100;
const unsigned Archer::archer_dfn = 100;
const unsigned Pig::pig_hp = 100;
const unsigned Pig::pig_atk = 100;
const unsigned Pig::pig_dfn = 100;

Alive::Alive(const std::string & name, unsigned hp, unsigned atk, unsigned dfn): name(name), hp(hp), atk(atk), dfn(dfn) {}

void Thing::Destroy(unsigned br) {
    brokenness += br;
    if (brokenness >= firmness)
        Destruct();
}

void Thing::Destruct() {
    this->~Thing();
}

Thing::Thing(const std::string & name, unsigned firm): name(name), firmness(firm), brokenness(0), owner(nullptr) {}

Thing::~Thing() {}

void Thing::SetOwner(Human * ptr) {
    owner = ptr;
}

Human * Thing::GetOwner() const {
    return owner;
}

Arsenal::Arsenal(const std::string & name, unsigned firm, unsigned atk): Thing(name, firm), atk(atk) {}

Arsenal::~Arsenal() {
    if (GetOwner())
        GetOwner()->ars = nullptr;
}

void Arsenal::Destruct() {
    this->~Arsenal();
}

Armor::Armor(const std::string & name, unsigned firm, unsigned dfn): Thing(name, firm), dfn(dfn) {}

Armor::~Armor() {
    if (GetOwner())
        GetOwner()->arm = nullptr;
}

void Armor::Destruct() {
    this->~Armor();
}

Human::Human(const std::string & name, bool gender, unsigned hp, unsigned atk, unsigned dfn, const std::set<std::string> & arsenals, const std::set<std::string> & armors): Alive(name, hp, atk, dfn), gender(gender), ars(nullptr), arm(nullptr), exp(0), arsenals(arsenals), armors(armors) {}

Human::~Human() {
    if (ars)
        ars->owner = nullptr;
    if (arm)
        arm->owner = nullptr;
}

void Human::TakeArsenal(Arsenal * pars) {
    if (arsenals.find(std::string(typeid(pars).name())) != arsenals.end() && pars->owner == nullptr) {
        ars = pars;
        pars->owner = this;
        // some printf
    }
    //else
        // some printf
}

void Human::TakeArmor(Armor * parm) {
    if (armors.find(std::string(typeid(parm).name())) != armors.end() && parm->owner == nullptr) {
        arm = parm;
        parm->owner = this;
        // some printf
    }
    //else
        // some printf
}

Farmer::Farmer(const std::string & name, bool gender): Human(name, gender, farmer_hp, farmer_atk, farmer_dfn, std::set<std::string>({std::string(typeid(Shovel).name())}), std::set<std::string>()) {}

Knight::Knight(const std::string & name, bool gender): Human(name, gender, knight_hp, knight_atk, knight_dfn, std::set<std::string>({std::string(typeid(Sword).name())}), std::set<std::string>({std::string(typeid(Lats).name())})) {}

Archer::Archer(const std::string & name, bool gender): Human(name, gender, archer_hp, archer_atk, archer_dfn, std::set<std::string>({std::string(typeid(Arch).name())}), std::set<std::string>({std::string(typeid(Chain).name())})) {}

Animal::Animal(const std::string & name, unsigned hp, unsigned atk, unsigned dfn): Alive(name, hp, atk, dfn) {}

Animal::~Animal() {}

Pig::Pig(const std::string & name, bool gender): Animal(name, pig_hp, pig_atk, pig_dfn) {}

void Battle(Alive * comp1, Alive * comp2) {
    // some actions with destroying of arsenals and armors
}
