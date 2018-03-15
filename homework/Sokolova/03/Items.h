/**
@file
@brief Header file with item classes declaration.

File contains hierarchy of buyable items in the game.
*/

/**
 * @brief Base class of all items.
 * Item has a unique id. 
 * Every item can be bought so has some cost.
 * Item can be worn out and can be renewed.
 * Item can be upgraded to new level.
 */
class Item {
    int id;
    int cost;
    int state;
    int level;
    int power;
public:
    void renew();
    void upgrade();
};

/**
 * @brief Base class of weapons.
 * Every weapon has a list of actions that can be done with it.
 * Weapon can attack.
 */
class Weapon: public Item {
    int actions[];
public:
    void attack(int action);
};

/**
 * @brief Bow attacks with arrows.
 * Available actions: shoot, beat with arc.
 * Main advantage: can be used from far of enemy.
 * Upgrade: increase number of arrows that can be used in a row.
 */
class Bow: public Weapon {
    int arrows;
};

/**
 * @brief Shovel attacks with blade.
 * Available actions: cut with blade, beat with handle.
 * Main advantage: can be used suddenly.
 * Upgrade: increase in weight and blade sharpening.
 */
class Shovel: public Weapon {
    int weight;
    int sharpness;
};

/**
 * @brief Sword attacks with blade.
 * Available actions: several special methods.
 * Main advantage: diversity of actions.
 * Upgrade: longen, sharpen.
 */
class Sword: public Weapon {
};

/**
 * @brief Base class of armor.
 * Main armor function is to defence.
 * Power defines the power of attack it can repel.
 */
class Armor: public Item {
public:
    void defence();
};

/**
 * @brief Hauberk can defend of shovel and somehow of arrows but cannot defend of sword.
 */
class Hauberk: public Armor {
};

/**
 * @brief Lats can defend of everything exept beats with heavy stuff.
 */
class Lats: public Armor {
};

/**
 * @brief Basin can defend of everything in one-to-one fight but is useless in far distance.
 */
class Basin: public Armor {
};
