#pragma once

#include "Tool.h"

class Weapon : public Tool {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Weapon(const char* name, unsigned int attack_rate, unsigned int attack_speed, const char* attack_type) : Tool(name) {
		type_ = "weapon";

		attack_rate_ = attack_rate;
		attack_speed_ = attack_speed;

		attack_type_ = attack_type;

		broken_ = false;
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	unsigned int attack_rate() const {
		return attack_rate_;
	}

	unsigned int attack_speed() const {
		return attack_speed_;
	}

	const char* attack_type() const {
		return attack_type_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Weapon() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	unsigned int attack_rate_;
	unsigned int attack_speed_;

	const char* attack_type_;
};