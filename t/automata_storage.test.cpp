#include <iostream>

#define DFA_TESTING
#include "../lib/AutomataStorage.h"
#include "../lib/Automaton.h"


void okay(bool test, std::string message) {
	if (test) {
		std::cout << "    Check! " << message << "\n";
	} else {
		std::cout << "    Fail! " << message << "\n";
	}
}

int main() {
	std::cout << "Testing storage of automatons\n";

	std::cout << "  Incrementing current identifier\n";
  AutomataStorage as = AutomataStorage();
	okay(as.currentIdentifier == 0, "Identifier is 0 at the beginning");
  as.Add(std::make_shared<Automaton>(Automaton(1)));
	okay(as.currentIdentifier == 1, "Identifier is 1 after adding one element");
  as.Add(std::make_shared<Automaton>(Automaton(2)));
	okay(as.currentIdentifier == 2, "Identifier is 2 after adding a second element");

	std::cout << "  Retrieving automaton\n";
	okay(as.Retrieve(1) != nullptr, "Automaton at identifier 1");
	okay(as.Retrieve(0) == nullptr, "No automaton at identifier 0");
	okay(as.Retrieve(5) == nullptr, "No automaton after storage boundaries");

  return 0;
}
