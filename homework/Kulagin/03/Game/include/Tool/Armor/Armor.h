#pragma once

#include "../Tool.h"

class Armor : public Tool {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Armor(const char* name, unsigned int defence_rate, const char* defence_type) : Tool(name) {
		type_ = "armor";

		defence_rate_ = defence_rate;
		defence_type_ = defence_type;

		broken_ = false;
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	unsigned int defence_rate() const {
		return defence_rate_;
	}

	const char* defence_type() const {
		return defence_type_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Armor() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	unsigned int defence_rate_;

	const char* defence_type_;
};