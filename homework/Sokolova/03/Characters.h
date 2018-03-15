/**
@file
@brief Header file with character classes declaration.

File contains hierarchy of characters in the game.
*/

#include <string>
#include "Items.h"


/**
 * @brief Base class of all characters in the game.
 * Has unique identifier and name.
 * Has some level that defines max value for characteristic.
 * Has age, power and health.
 * Can recover of damage and upgrade to new level.
 */

class Character {
    int id;
    std::string Name;
protected:
    int health;
    int power;
    int age;
    int sex;
    int level;
public:
    void recover();
    void upgrade();
};


/**
 * @brief Base class of all animal characters.
 * Has some appearance characteristics.
 * Can work and challenge with other animals.
 */
class Animal: public Character {
    int furColor;
public:
    void work();
};

/**
 * @brief Horse can carry its human and take part in horseraces.
 */
class Horse: public Animal {
public:
    void carryMan();
    void participateHorseracaes();
};

/**
 * @brief Pig can put on weight and take part in pig exhibition.
 */
class Pig: public Animal {
public:
    void growFat();
    void participateExhibition();
};


/**
 * @brief Base class of human characters.
 * Has some appearance characteristics.
 * Has money to buy items.
 * Can attack, communicate, buy items and earn money with bets.
 */
class Human: public Character {
    int skinColor;
    int hairColor;
    int money;
public:
    void attack(Weapon *weapon, Human &enemy);
    void buyItem(Item *item);
    void communicate(Character &companion);
    void bet(Character &character);
};

/**
 * @brief Archer have a bow and hauberk.
 * Can have a horse.
 * Earns money by participating in archery challenges.
 */
class Archer: public Human {
    Horse *horse;
    Bow *bow;
    Hauberk *hauberk;
public:
    void participateTargetArchery();
};

/**
 * @brief Peasant have a shovel and basin.
 * Can have a pig.
 * Earns money by digging and pork selling.
 */
class Peasant: public Human {
    Pig *pig;
    Shovel *shovel;
    Basin *basin;
public:
    void dig();
    void sellPork();
};

/**
 * @brief Knight have a sword and lats.
 * Can have a horse.
 * Earns money by participating tournaments.
 */
class Knight: public Human {
    Horse *horse;
    Sword *sword;
    Lats *lats;
public:
    void participateTournament();
};
