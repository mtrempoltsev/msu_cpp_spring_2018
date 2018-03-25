#include <list>
#include <vector>
#include <functional>

enum class UnitState{
	NOT_SET, LIFE, DEAD
};
enum class ArmorType {
	NOT_SET, HEAD, SHOULDRES, HANDS, CHEST, BRACER, PAINTS, BOOTS, FINGER
};
enum class ItemState {
	NOT_SET, LIFE, BROKEN
};

struct Position{
	float x;
	float y;
	float z;
};
class Unit {
public:
	std::string getName() {
		return name;
	}
	UnitState getState() {
		return state;
	}
	void setState(UnitState state) {
		this->state = state;
		notifyListener();
	}
	Position getPosition() {
		return position;
	}
	void setPosition(Position position) {
		this->position = position;
		notifyListener();
	}
	float getHp() {
		return hp;
	}
	float getMaxHp() {
		return maxHp;
	}
	void setHp(float hp) {
		this->hp = hp;
		notifyListener();
	}
	void setListener(std::function<void()> listener) {
		this->listener = listener;
		notifyListener();
	}
protected:
	std::string name;
	float maxHp;
	void notifyListener() {
		if (!listener)
			listener();
	}
private:
	UnitState state;
	Position position;
	float hp;
	std::function<void()> listener;
};
class Armor;
class Weapon;
struct WeaponUser {
	virtual bool equipWeapon(Weapon* weapon) = 0;
	virtual Weapon* getWeapon() = 0;
	virtual void dropWeapon() = 0;
	virtual void hit(Unit* unit) = 0;
};
struct ArmorUser {
	virtual bool equipArmor(Armor* armor) = 0;
	virtual Armor* getArmor(ArmorType type) = 0;
	virtual void dropArmor(ArmorType type) = 0;
};
class Item {
public:
	std::string getName(){
		return name;
	}
	ItemState getState() {
		return state;
	}
	void setState(ItemState state) {
		this->state = state;
		notifyListener();
	}
	void setHp(float hp) {
		this->hp = hp;
		notifyListener();
	}
	float getHp() {
		return hp;
	}
	float getMaxHp(){
		return maxHp;
	}
	float getWeight() {
		return weight;
	}
	void setListener(std::function<void()> listener) {
		this->listener = listener;
		notifyListener();
	}
protected:
	std::string name;
	float weight;
	float maxHp;
	void notifyListener() {
		if (!listener)
			listener();
	}
private:
	ItemState state;
	float hp;
	std::function<void()> listener;
};

class Weapon: public Item {
public:
	float getAttack() {
		return attack;
	}
	float getAttackSpeed() {
		return attackSpeed;
	}
	float getAttackRange() {
		return attackRange;
	}
protected:
	float attack;
	float attackSpeed;
	float attackRange;
};


class Armor : public Item{
public:
	float getDeffence() {
		return deffence;
	}
	ArmorType getType() {
		return type;
	}
protected:
	float deffence;
	ArmorType type;
};
class Holder;
class RangeWeapon : public Weapon {
public:
	Holder* getHolder() {
		return holder;
	}
	void shot() {
		//надо дописать
	}
protected:
	Holder* holder;
};

class Bullet {
public:
	std::string getName() {
		return name;
	}
	float getDamage() {
		return damage;
	}
protected:
	std::string name;
	float damage;
};
class Holder {
public:
	std::string getName() {
		return name;
	}
	int getCapacity() {
		return capacity;
	}
	const std::list<Bullet*>& getBulletsCharged() {
		return bulletCharged;
	}
	size_t getBulletsChargedCount() {
		return bulletCharged.size();
	}
	bool chargeBullets(std::list<Bullet*>* bullets) {
		if (bullets->size() > getBulletsChargedCount())
			return false;
		else 
			bulletCharged.splice(bulletCharged.end(), *bullets);
	}
	bool hasNextBullet() {
		return bulletCharged.size() > 0;
	}
	Bullet* popBoollet() {
		Bullet* b = bulletCharged.back();
		bulletCharged.pop_back();
		return b;
	}

protected:
	std::string name;
	int capacity;
private:
	std::list<Bullet*> bulletCharged;
};

class Humanoid : public Unit, public WeaponUser, public  ArmorUser {
public:
	bool equipWeapon(Weapon* weapon) override {
		this->weapon = weapon;
	}
	Weapon* getWeapon() override {
		return weapon;
	}
	void dropWeapon() override {
		weapon = 0;
	}
	void hit(Unit* unit) override {
		//некоторая реализация
	}

	bool equipArmor(Armor* armor) override {
		//реализация с учётом weaponsAviable и уже надетых вещей
	}
	Armor* getArmor(ArmorType type) override {

	}
	void dropArmor(ArmorType type) override {
		//скинуть надетую броню с некоторой части тела
	}
private:
	Weapon* weapon;
	std::vector<std::string> weaponsAviable;
	std::vector<Armor> armors;
};
class Archer : public Humanoid{};
class Knight : public Humanoid{};
class Peasant: public Humanoid{};
class Pig: public Unit{};
class Arrow: public Bullet{};
class Quiver: public Holder{};
class Bow: public RangeWeapon{};
class Sword: public Weapon{};
class Showel: public Weapon{};
class Mail: public Armor{};
class Lats: public Armor{};
class Helm: public Armor{};
