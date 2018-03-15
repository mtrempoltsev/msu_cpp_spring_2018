#pragma once

#include "../Tool.h"

class Weapon : protected Tool {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Weapon(string_t name, uint_t attack_rate, uint_t attack_speed, string_t attack_type) :
		Tool(name, "weapon", false),

		attack_rate_(attack_rate),
		attack_speed_(attack_speed),
		attack_type_(attack_type) {
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	uint_t attack_rate() const {
		return attack_rate_;
	}

	uint_t attack_speed() const {
		return attack_speed_;
	}

	string_t attack_type() const {
		return attack_type_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Weapon() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	uint_t attack_rate_;
	uint_t attack_speed_;

	string_t attack_type_;
};