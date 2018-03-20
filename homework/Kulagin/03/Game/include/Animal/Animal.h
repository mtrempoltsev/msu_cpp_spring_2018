#pragma once

#include "../types.h"
#include "../constants.h"

class Animal {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Animal(string_t type = UNKNOWN, uint_t total_hp = 1, uint_t speed = 1, uint_t level = 1) :
		type_(type),

		hp_(total_hp),
		total_hp_(total_hp),

		speed_(speed),
		level_(level) {
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	string_t type() const {
		return type_;
	}

	uint_t hp() const {
		return hp_;
	}

	uint_t total_hp() const {
		return total_hp_;
	}

	uint_t speed() const {
		return speed_;
	}

	uint_t level() const {
		return level_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	virtual ~Animal() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

protected:
	string_t type_;

	uint_t hp_;
	uint_t total_hp_;

	uint_t speed_;
	uint_t level_;
};