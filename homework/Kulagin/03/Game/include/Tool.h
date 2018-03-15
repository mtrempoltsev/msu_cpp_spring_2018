#pragma once

class Tool {

public:
	Tool(const char* name, bool broken = false): name_(name), broken_(broken) {}

	void broke() {}

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	const char* name() {
		return name_;
	}

	const char* type() const {
		return type_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	bool broken() const {
		return broken_;
	}

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	virtual ~Tool() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

protected:
	const char* name_;
	const char* type_;

	bool broken_;
};