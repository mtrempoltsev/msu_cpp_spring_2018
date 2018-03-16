#pragma once

#include "../Tool.h"

class Weapon : public Tool {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Weapon(string_t name, string_t weapon_type, uint_t attack_rate, uint_t attack_speed, string_t attack_type) :
		Tool("weapon", name, false),

		weapon_type_(weapon_type),

		attack_rate_(attack_rate),
		attack_speed_(attack_speed),
		attack_type_(attack_type) {
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	string_t weapon_type() const {
		return weapon_type_;
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
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Weapon() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	string_t weapon_type_;

	uint_t attack_rate_;
	uint_t attack_speed_;

	string_t attack_type_;
};