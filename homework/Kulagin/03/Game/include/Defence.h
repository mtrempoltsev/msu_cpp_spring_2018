#pragma once

#include "Tool.h"

class Armor : Tool {

public:
	Armor(unsigned int _rate, const char _type) {
		rate_ = _rate;
		type_ = _type;
	}

	~Armor() {}

private:
	unsigned int rate_;
	const char* type_;
};