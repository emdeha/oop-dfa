#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"


int main() {
  std::cout << "Testing IsEmpty on automaton\n";

  Automaton a;
  a.type = Empty;
  T::okay(a.IsEmpty() == true, "Automaton of type Empty should be empty");
  a.next = std::make_shared<Automaton>();
  T::okay(a.IsEmpty() == true,
      "Automaton of type Empty should be empty regardless of other data");
  a.type = Character;
  T::okay(a.IsEmpty() == false,
      "Automaton of other type than Empty is not empty");

  return 0;
}
