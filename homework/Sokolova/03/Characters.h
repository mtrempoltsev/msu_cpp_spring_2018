/**
@file
@brief Header file with character classes declaration.

File contains hierarchy of characters in the game.
*/

#include <string>
#include "Items.h"


/**
 * @brief Base class of all characters in the game.
 * Can recover of damage and upgrade to new level.
 */

class Character {
public:
    void recover();
    void upgrade();
};


/**
 * @brief Base class of all animal characters.
 * Identified by id, name.
 * Recovers by increasing power.
 * Upgrades by increasing its level.
 * Can work and challenge with other animals.
 */
class Animal: public Character {
    int id;
    std::string name;
    int level;
    int power;
public:
    void work();
    void challenge(Animal &);
};

/**
 * @brief Horse works by carrying its human taking part in horseraces.
 */
class Horse: public Animal {
    void carryMan();
    void participateHorseraces();
};

/**
 * @brief Pig works by putting weight on and taking part in pig exhibition.
 */
class Pig: public Animal {
    void growFat();
    void participateExhibition();
};


/**
 * @brief Base class of human characters.
 * Identified by id and name.
 * Has level, power and health characteristics.
 * Recovers by increasing health.
 * Upgrades by increasing level.
 * Has money to buy items.
 * Can attack, communicate, buy items and earn money with bets.
 */
class Human: public Character {
    int id;
    std::string name;
    int level;
    int power;
    int healht;
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
