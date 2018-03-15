#pragma once

class Player {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Player(unsigned int attack_rate = 0, unsigned int attack_speed = 0, const char* att = "None") {

	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	const char* name() const {
		return name_;
	}

	unsigned int attack_rate() const {
		return attack_rate_;
	}

	unsigned int attack_speed() const {
		return attack_speed_;
	}

	const char* attack_type() const {
		return attack_type_;
	}

	unsigned int hp() const {
		return hp_;
	}

	unsigned int total_hp() const {
		return total_hp_;
	}

	unsigned int level() const {
		return level_;
	}

	unsigned int experience() const {
		return experience_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------


	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	void set_name(const char* name) {
		name_ = name;
	}

	void set_hp(unsigned int hp) {
		hp_ = hp;
	}

	void set_total_hp(unsigned int total_hp) {
		total_hp_ = total_hp;
	}

	void set_level(unsigned int level) {
		level_ = level;
	}

	void set_experience(unsigned int experience) {
		experience_ = experience;
	}
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	virtual ~Player() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

protected:
	const char* type_;

	const char* name_;

	unsigned int hp_;
	unsigned int total_hp_;

	unsigned int level_;
	unsigned int experience_;

	unsigned int attack_rate_;
	unsigned int attack_speed_;

	const char* attack_type_;
};



// #pragma once

// #include <cstdio>
// #include <typeinfo>
// #include <map>

// #include "Unit.h"

// class Player : Unit {

// public:
// 	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
// 	Player(): Unit() {
// 		attack_rate_ = 10;
// 		attack_speed_ = 10;
// 		attack_type_ = "pierce";
// 	}
// 	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

// 	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
// 	void set_name(const char* name) {
// 		name_ = name;
// 	}

// 	void set_hp(unsigned int hp) {
// 		hp_ = hp;
// 	}

// 	void set_total_hp(unsigned int total_hp) {
// 		total_hp_ = total_hp;
// 	}
// 	// END------------------------------------------------ SETTERS ----------------------------------------------------

// 	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
// 	const char* name() const {
// 		return name_;
// 	}

// 	unsigned int hp() const {
// 		return hp_;
// 	}

// 	unsigned int total_hp() const {
// 		return total_hp_;
// 	}
// 	// END------------------------------------------------ GETTERS ----------------------------------------------------

// 	void add_tool(Tool* tool) {
// 		tools_[tool->name()] = tool;
// 	}

// 	void remove_tool(Tool* tool) {
// 		delete tools_[tool->name()];
// 	}

// 	void set_weapon(const char* name) {
// 		for (auto k : tools_) {
// 			if (k.first == name && (k.second)->type() == "weapon") {
// 				weapon_ = (Weapon*)k.second;
// 				return;
// 			}
// 		}

// 		printf("No such weapon\n");
// 		exit(1);
// 	}

// 	void set_armor(const char* name) {
// 		for (auto k : tools_) {
// 			if (k.first == name && (k.second)->type() == "armor") {
// 				armor_ = (Armor*)k.second;
// 				return;
// 			}
// 		}

// 		printf("No such armor\n");
// 		exit(1);
// 	}

// 	void print_tools() {
// 		for (auto k : tools_) {
// 			printf("%s\t", k.first);
// 		}

// 		printf("\n");
// 	}

// 	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
// 	~Player() {}
// 	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

// private:
// 	const char* name_;

// 	unsigned int hp_;
// 	unsigned int total_hp_;

// 	Weapon* weapon_;
// 	Armor* armor_;

// 	std::map<const char*, Tool*> tools_;
// };