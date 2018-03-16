#pragma once

#include <map>

#include "../Tool/Weapon/Weapon.h"
#include "../Tool/Armor/Armor.h"

class Player {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Player(string_t type, uint_t attack_rate = 0, uint_t attack_speed = 0, string_t att = "None") {

	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	string_t name() const {
		return name_;
	}

	uint_t attack_rate() const {
		return attack_rate_;
	}

	uint_t attack_speed() const {
		return attack_speed_;
	}

	string_t attack_type() const {
		return attack_type_;
	}

	uint_t hp() const {
		return hp_;
	}

	uint_t total_hp() const {
		return total_hp_;
	}

	uint_t level() const {
		return level_;
	}

	uint_t experience() const {
		return experience_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------


	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	void set_name(string_t name) {
		name_ = name;
	}

	void set_hp(uint_t hp) {
		hp_ = hp;
	}

	void set_total_hp(uint_t total_hp) {
		total_hp_ = total_hp;
	}

	void set_level(uint_t level) {
		level_ = level;
	}

	void set_experience(uint_t experience) {
		experience_ = experience;
	}
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	void add_tool(Tool* tool) {
		tools_[tool->name()] = tool;
	}

	void set_weapon(string_t name) {
		for (auto k : tools_) {
			if (k.first == name && (k.second)->type() == "weapon") {
				weapon_ = static_cast<Weapon*>(k.second);
				return;
			}
		}

		printf("No such weapon\n");
		exit(1);
	}

	void set_armor(string_t name) {
		for (auto k : tools_) {
			printf("%s %s\n", k.first, k.second->type());
			if (k.first == name && (k.second)->type() == "armor") {
				armor_ = static_cast<Armor*>(k.second);
				return;
			}
		}

		printf("No such armor\n");
		exit(1);
	}

	void print_tools(string_t header = "") {
		if (header) {
			printf("%s\n", header);
		}

		for (auto k : tools_) {
			printf("\t%s\n", k.first);
		}

		printf("\n");
	}

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	virtual ~Player() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

protected:
	string_t type_;

	string_t name_;

	uint_t hp_;
	uint_t total_hp_;

	uint_t level_;
	uint_t experience_;

	uint_t attack_rate_;
	uint_t attack_speed_;

	string_t attack_type_;


	Weapon* weapon_;
	Armor* armor_;

	std::map<string_t, Tool*> tools_;
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
// 	void set_name(string_t name) {
// 		name_ = name;
// 	}

// 	void set_hp(uint_t hp) {
// 		hp_ = hp;
// 	}

// 	void set_total_hp(uint_t total_hp) {
// 		total_hp_ = total_hp;
// 	}
// 	// END------------------------------------------------ SETTERS ----------------------------------------------------

// 	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
// 	string_t name() const {
// 		return name_;
// 	}

// 	uint_t hp() const {
// 		return hp_;
// 	}

// 	uint_t total_hp() const {
// 		return total_hp_;
// 	}
// 	// END------------------------------------------------ GETTERS ----------------------------------------------------

// 	void add_tool(Tool* tool) {
// 		tools_[tool->name()] = tool;
// 	}

// 	void remove_tool(Tool* tool) {
// 		delete tools_[tool->name()];
// 	}

// 	void set_weapon(string_t name) {
// 		for (auto k : tools_) {
// 			if (k.first == name && (k.second)->type() == "weapon") {
// 				weapon_ = (Weapon*)k.second;
// 				return;
// 			}
// 		}

// 		printf("No such weapon\n");
// 		exit(1);
// 	}

// 	void set_armor(string_t name) {
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
// 	string_t name_;

// 	uint_t hp_;
// 	uint_t total_hp_;

// 	Weapon* weapon_;
// 	Armor* armor_;

// 	std::map<string_t, Tool*> tools_;
// };