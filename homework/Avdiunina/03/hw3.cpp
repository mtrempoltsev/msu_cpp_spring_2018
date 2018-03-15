//
// Created by polina997 on 3/12/18.
//


class Weapon {

public:
    int attack() {
        if (this->durability == 0) {
            // Выкинуть исключение?
            return 0;
        }
        else {
            this->durability--;
            return this->power;
        }
    }

protected:
    int power;
    int durability;
};


class Bow : Weapon {

public:
    Bow() : Weapon() {
        this->durability = 10;
        this->power = 5;
    }
};


class Sword : Weapon {

public:
    Sword() : Weapon() {
        this->durability = 20;
        this->power = 10;
    }
};


class Shovel : Weapon {

public:
    Shovel() : Weapon() {
        this->durability = 7;
        this->power = 3;
    }
};


class Armor {
public:
    int hit() {
        if (this->strength == 0) {
            // Выкинуть исключение?
            return 0;
        }
        else {
            this->strength--;
            this->armor_life--;
            return this->armor_life;
        }
    }

protected:
    int strength;
    int armor_life;

};

class Lats  : Armor {

public:
    Lats() : Armor() {
        this->strength = 10;
        this->armor_life = 10;
    }
};

class Chain_Armor : Armor {

public:
    Chain_Armor() : Armor() {
        this->strength = 20;
        this->armor_life = 20;
    }
};


class Animal {
public:
    int use() {
        if (this->life == 0) {
            // Выкинуть исключение?
            return 0;
        }
        else {
            this->life--;
            this->food++;
            return this->food;
        }
    }

protected:
    int food;
    int life;
};

class Pig : Animal {

public:
    Pig() : Animal() {
        this->food = 5;
        this->life = 3;
    }
};


class Character {

public:

    int defend(Character* enemy, int damage) {
        if (this->armor == nullptr || this->armor->armor_life <= 0) {
            // Броня сломалась, получаем урон
            // вызвать генерацию нового void equipNewArmor(Armor* armor)
            this->health -= damage;
        }
        else {
            this->armor->hit();
        }
        return this->health;

    }

    bool attack(Character* enemy) {
        if (this->weapon == nullptr || this->weapon->durability == 0) {
            // Оружие сломалось, нужно вызвать генерацию нового void equipNewWeapon(Weapon* weapon)
            return false;
        }
        else {
            int damage = this->weapon->attack();
            if (damage == 0) {
                // Ошибочка вышла
                return false;
            }
            enemy->defend(this);
            return true;
        }
    };

    int improve_health(){
        if (this->health == 0){
            std::cout << "Game over" << std::endl;
        }
        if(this->animal){
            this->health += this->animal->use();
        }
        return this->health;

    }

    void equipNewWeapon(Weapon* weapon) {};
    void equipNewArmor(Armor* armor) {};


protected:
    int health;
    Weapon* weapon;
    Armor* armor;
    Animal* animal;
};

class Archer: Character {
    Archer(): Character() {
        this->health = 100;
        this->weapon = new Bow();
        this->armor = new Chain_Armor();
    }
};

class Knight: Character {
        Knight(): Character() {
            this->health = 200;
            this->weapon = new Sword();
            this->armor = new Lats();
        }
};

class Peasant: Character {
        Peasant(): Character() {
            this->health = 70;
            this->weapon = new Shovel();
            this->animal = new Pig();
        }
};
