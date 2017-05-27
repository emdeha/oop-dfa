#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/AutomataStorage.h"
#include "../../lib/Automaton.h"


int main() {
  std::cout << "Testing storage of automatons\n";

  std::cout << "  Incrementing current identifier\n";
  AutomataStorage as = AutomataStorage();
  T::okay(as.currentIdentifier == 0, "Identifier is 0 at the beginning");
  as.Add(std::make_shared<Automaton>(Automaton(1)));
  T::okay(as.currentIdentifier == 1, "Identifier is 1 after adding one element");
  as.Add(std::make_shared<Automaton>(Automaton(2)));
  T::okay(as.currentIdentifier == 2, "Identifier is 2 after adding a second element");

  std::cout << "  Retrieving automaton\n";
  T::okay(as.Retrieve(1) != nullptr, "Automaton at identifier 1");
  T::okay(as.Retrieve(0) == nullptr, "No automaton at identifier 0");
  T::okay(as.Retrieve(5) == nullptr, "No automaton after storage boundaries");

  std::cout << "  Listing all automatons\n";
  auto automatons = as.List();
  T::okay(automatons.size() == 2, "Has two automatons");
  T::okay(automatons[0] == 1, "First automaton has identifier 1");
  T::okay(automatons[1] == 2, "Second automaton has identifier 2");

  return 0;
}
