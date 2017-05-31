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
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Split, '\0');
  a.next->next = std::make_shared<Automaton>(Character, 'b');
  a.next->next->next = std::make_shared<Automaton>(Match, '\0');
  a.next->nextSplit = std::make_shared<Automaton>(Character, 'c');
  a.next->nextSplit->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.ToSerial() == "(Character 'a' "
                          "(Split (Character 'b' (Match)) (Character 'c' (Match))))",
      "Serializes a simple split");

  // Recongnizes "a(a|b)cd(e|(f|d))"
  Automaton b(Character, 'a');
  b.next = std::make_shared<Automaton>(Split, '\0');
  b.next->next = std::make_shared<Automaton>(Character, 'a');
  b.next->nextSplit = std::make_shared<Automaton>(Character, 'b');
  auto halfA = std::make_shared<Automaton>(Character, 'c');
  halfA->next = std::make_shared<Automaton>(Character, 'd');
  halfA->next->next = std::make_shared<Automaton>(Split, '\0');
  halfA->next->next->next = std::make_shared<Automaton>(Character, 'e');
  halfA->next->next->next->next = std::make_shared<Automaton>(Match, '\0');
  halfA->next->next->nextSplit = std::make_shared<Automaton>(Split, '\0');
  halfA->next->next->nextSplit->next = std::make_shared<Automaton>(Character, 'f');
  halfA->next->next->nextSplit->next->next = std::make_shared<Automaton>(Match, '\0');
  halfA->next->next->nextSplit->nextSplit = std::make_shared<Automaton>(Character, 'd');
  halfA->next->next->nextSplit->nextSplit->next = std::make_shared<Automaton>(Match, '\0');
  b.next->next->next = halfA;
  b.next->next->nextSplit = halfA;
  b.next->nextSplit->next = b.next->next->next;
  T::okay(b.ToSerial() == "(Character 'a' (Split"
      " (Character 'a' (Character 'c' (Character 'd' (Split"
        " (Character 'e' (Match))"
        " (Split (Character 'f' (Match)) (Character 'd' (Match)))))))"
      " (Character 'b' (Character 'c' (Character 'd' (Split"
        " (Character 'e' (Match))"
        " (Split (Character 'f' (Match)) (Character 'd' (Match)))))))))",
      "Serializes a more complex split");
}

int main() {
  std::cout << "Testing automaton serialization\n";

  std::cout << "  Saving to serial string\n";
  TestSerializingALinearAutomaton();
  TestSerializingASplitAutomaton();

  std::cout << "  Creation from serial string\n";

  return 0;
}
