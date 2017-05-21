#pragma once

#include <iostream>


namespace T {
void okay(bool test, std::string message) {
	if (test) {
		std::cout << "    Check! " << message << "\n";
	} else {
		std::cout << "    Fail! " << message << "\n";
	}
}
}
