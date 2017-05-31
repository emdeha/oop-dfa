#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"


void TestSerializingALinearAutomaton() {
  Automaton a(Match, '\0');
  T::okay(a.ToSerial() == "(Match)",
      "Serializes a match");

  Automaton b(Character, 'a');
  T::okay(b.ToSerial() == "(Character 'a')",
      "Serializes a character");
  b.next = std::make_shared<Automaton>(Character, 'b');
  T::okay(b.ToSerial() == "(Character 'a' (Character 'b'))",
      "Serializes two characters");
  b.next->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(b.ToSerial() == "(Character 'a' (Character 'b' (Match)))",
      "Serializes two characters followed by a match");
  b.next->next->next = std::make_shared<Automaton>(Character, 'c');
  T::okay(b.ToSerial() == "(Character 'a' (Character 'b' (Match)))",
      "Ignores Character after a Match.");
}

void TestSerializingASplitAutomaton() {
}

int main() {
  std::cout << "Testing automaton serialization\n";

  std::cout << "  Saving to serial string\n";
  TestSerializingALinearAutomaton();
  TestSerializingASplitAutomaton();

  std::cout << "  Creation from serial string\n";

  return 0;
}
