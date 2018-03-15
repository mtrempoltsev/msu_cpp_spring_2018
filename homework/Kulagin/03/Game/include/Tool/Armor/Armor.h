#pragma once

#include "../Tool.h"

class Armor : protected Tool {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Armor(string_t name, uint_t defence_rate, string_t defence_type) :
		Tool(name, "armor", false),

		defence_rate_(defence_rate),
		defence_type_(defence_type)
	{

	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	uint_t defence_rate() const {
		return defence_rate_;
	}

	string_t defence_type() const {
		return defence_type_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Armor() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	uint_t defence_rate_;

	string_t defence_type_;
};