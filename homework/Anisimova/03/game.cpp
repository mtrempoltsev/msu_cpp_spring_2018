#include "game.h"

const unsigned Farmer::farmer_hp = 100;
const unsigned Farmer::farmer_attack = 80;
const unsigned Farmer::farmer_defense = 100;
const unsigned Knight::knight_hp = 100;
const unsigned Knight::knight_attack = 100;
const unsigned Knight::knight_defense = 80;
const unsigned Archer::archer_hp = 100;
const unsigned Archer::archer_attack = 100;
const unsigned Archer::archer_defense = 80;
const unsigned Pig::pig_hp = 100;
const unsigned Pig::pig_attack = 10;
const unsigned Pig::pig_defense = 10;

Existence::Existence(const std::string & name, unsigned hp, unsigned attack, unsigned defense): name(name), hp(hp), attack(attack), defense(defense) {}

void Item::Destroy(unsigned br) {
    brokenness += br;
    if (brokenness >= firmness)
        broken = true;

}

Item::Item(const std::string & name, unsigned firm): name(name), firmness(firm), brokenness(0), owner(nullptr), broken(false) {}

void Item::SetOwner(Human * ptr) {
    owner = ptr;
}

Human * Item::GetOwner() const {
    return owner;
}

void Item::RemoveOwner() {
    owner = nullptr;
}

Arsenal::Arsenal(const std::string & name, unsigned firm, unsigned attack): Item(name, firm), attack(attack) {}

Arsenal::~Arsenal() {
    if (GetOwner())
        GetOwner()->RemoveArsenal();
}

Armor::Armor(const std::string & name, unsigned firm, unsigned defense): Item(name, firm), defense(defense) {}

Armor::~Armor() {
    if (GetOwner())
        GetOwner()->RemoveArmor();
}

std::string Shovel::NameOfClass() const {
    return "Shovel";
}

std::string Sword::NameOfClass() const {
    return "Sword";
}

std::string Arch::NameOfClass() const {
    return "Arch";
}

std::string Lats::NameOfClass() const {
    return "Lats";
}

std::string Chain::NameOfClass() const {
    return "Chain";
}

Human::Human(const std::string & name, bool gender, unsigned hp, unsigned attack, unsigned defense, const std::set<std::string> & arsenals, const std::set<std::string> & armors): Existence(name, hp, attack, defense), gender(gender), ars(nullptr), arm(nullptr), exp(0), arsenals(arsenals), armors(armors) {}

Human::~Human() {
    if (ars)
        ars->SetOwner(nullptr);
    if (arm)
        arm->SetOwner(nullptr);
}

void Human::TakeArsenal(Arsenal * pars) {
    if (arsenals.find(pars->NameOfClass()) != arsenals.end() && pars->GetOwner() == nullptr && ars == nullptr) {
        ars = pars;
        pars->SetOwner(this);

    }

}

void Human::TakeArmor(Armor * parm) {
    if (armors.find(parm->NameOfClass()) != armors.end() && parm->GetOwner() == nullptr && arm == nullptr) {
        arm = parm;

    }

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

Farmer::Farmer(const std::string & name, bool gender): Human(name, gender, farmer_hp, farmer_attack, farmer_defense, std::set<std::string>({"Shovel"}), std::set<std::string>()) {}

Knight::Knight(const std::string & name, bool gender): Human(name, gender, knight_hp, knight_attack, knight_defense, std::set<std::string>({"Sword"}), std::set<std::string>({"Lats"})) {}

Archer::Archer(const std::string & name, bool gender): Human(name, gender, archer_hp, archer_attack, archer_defense, std::set<std::string>({"Arch"}), std::set<std::string>({"Chain"})) {}

Animal::Animal(const std::string & name, unsigned hp, unsigned attack, unsigned defense): Existence(name, hp, attack, defense) {}

Pig::Pig(const std::string & name, bool gender): Animal(name, pig_hp, pig_attack, pig_defense) {}

void Battle(Existence * comp1, Existence * comp2) {

//some actions with change of parametrs of user 1 and user 2

}
