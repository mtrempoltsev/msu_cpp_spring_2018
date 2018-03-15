class Characteristics {
  int health;
  int location;
  int esurience;
};

class Animal : public Characteristics {
  const int edibility;
  const int threat_to_life;
};

class Pig : public Animal {};

class Wolf : public Animal {};

class Fish : public Animal {};

class Indicators {
  int cost;
  int availability;
};

class Weapon : public Indicators {
  const int damage;
};

class Shovel : public Weapon {};

class Steel : public Weapon {};

class Bow : public Weapon {};

class Armor : public Indicators {
  const int defense;
};

class Hauberk : public Armor {};

class Lats : public Armor {};

class Helmet : public Armor {};

class Person : public Characteristics {
  const int max_health;
  const int max_esurience;
  const int base_damage;
  const int base_defense;
  Animal *animal;
};

class Peasant : public Person {
  Shovel *weapon;
  Helmet *armor_1;
  Hauberk *armor_2;
};

class Knight : public Person {
  Steel *weapon;
  Armor *armor;
};

class Bowman : public Person {
  Bow *weapon;
  Helmet *armor;
};



int main () {
}
