// Базовый класс для всех предметов.
// Поля:
// name - название предмета (т.е. например "длинный меч" и "короткий меч")
// max_durability - максимальная прочность.
// durability - прочность. Когда <= 0 - предмет ломается (исчезает из игры).
class Item
{
    const std::string name;
    const int max_durability;
    int durability;
};

// Базовый класс для оружия.
// Поля:
// damage - бонусный урон оружия.
// distance - максимальная дальность атаки оружия.
class Weapon: public Item
{
    const int damage;
    const int distance;
};

class Sword: public Weapon {};

class Bow: public Weapon {};

class Pickaxe: public Weapon {};

// Базовый класс для брони.
// Поля:
// defence - бонусная защита.
class Armor: public Item
{
    const int defence;
};

class Plate: public Armor {};

class ChainArmor: public Armor {};

// Базовый класс для всех живых существ.
// Поля:
// name - имя существа
// max_health - максимальное значение HP существа.
// health - HP существа.
class Creature
{
    const std::string name;
    const int max_health;
    int health;
};

// Базовый класс для всех животных.
class Animal: public Creature {};

class Pig: public Animal {};

class Horse: public Animal {};

// Базовый класс для всех людей.
// Поля:
// base_damage - базовый урон, т.е. урон без оружия
// base_defence - базовая защита, т.е. защита без брони.
class Human: public Creature
{
    const int base_damage;
    const int base_defence;
};

// Рыцари. Могут иметь меч в качестве оружия, латы в качвестве брони и лошадь в качестве ездового животного.
class Knight: public Human
{
    Sword *weapon;
    Plate *armor;
    Horse *mount;
}

// Лучники. Могут иметь лук в качестве оружия и кольчугу в качестве брони.
class Archer: public Human
{
    ChainArmor *armor;
    Bow *weapon;
}

// Крестьяне. Могут иметь кирку в качестве оружия и свиней в качестве домашнего скота.
class Peasant: public Human
{
    Pickaxe *weapon;
    Pig *livestock;
}