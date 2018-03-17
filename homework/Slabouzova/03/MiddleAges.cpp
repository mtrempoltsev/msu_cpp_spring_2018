#include "glm/common.hpp"
#include <string>
#include <vector>


// the base object
class Object
{
private:
	float hp;
	glm::vec3 location;
	std::string model_path;
public:
	/*some methods*/
};


//  	  start of big branch with units (someone alive)
class Unit: public Object
{
private:
	float speed;
	float aggression;
	std::string name;
public:
	/*some methods*/	
};


class Animal;
class Item;
class Weapon;
class Armor;


// branch with people 
class Person: public Unit
{
private:
	float money;
	Weapon* weapon;
	Armor* armor;
	Animal* current_animal; 
	std::vector<Animal*> animal_list;
	std::vector<Item*> inventory;
public:
	/*some methods*/	
};

class Knight: public Person { };
class Bowman: public Person { };
class Countryman: public Person { };


// branch with animals
class Animal: public Unit
{
private:
	float power;
	bool is_tamed;
	std::string skin;
	Person* owner;
public:
	/*some methods*/	
};

class Horse: public Animal { };
class Dragon: public Animal { };
class Pig: public Animal { };
//		  end of branch with units


//  	  start of the 2nd big branch - items

class Item: public Object
{
private:
	Person* owner;
	float weight;
public:
	/*some methods*/	
};

class Armor: public Item { };
class Shovel: public Item 
{ 
	float defense; 
};
class Weapon: public Item
{
	float damage;
	float distance;
	std::string type;
public:
	/*some methods*/		
};

class Sword: public Weapon { };
class Bow: public Weapon { };
//		  end of branch with items



int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
