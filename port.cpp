#include "port.h"
#include <cstdlib>


Port::Port(String pattern) : Field(pattern, PORT) {
}

bool Port::set_value(String val) {
	String *low_high;
	size_t low_high_size;
	val.split("-", &low_high, &low_high_size);
	if (low_high_size == 2) {
		this->range[0] = low_high[0].trim().to_integer();
		this->range[1] = low_high[1].trim().to_integer();
		if (range[0] <= 65535 && range[0] >= 0 && range[1] <= 65535 && range[1] >= 0 &&
			range[0] <= range[1]) {
			delete[] low_high;
			return true;
		}
	}
	delete[] low_high;
	return false;
}

bool Port::match_value(String val) const {
	int checkval = val.trim().to_integer();
	if (range[0] <= checkval && checkval <= range[1]) {
		return true;
	}
	else {
		return false;
	}
}