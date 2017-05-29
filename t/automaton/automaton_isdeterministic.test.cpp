#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"


void TestWordAB() {
  /*
   * An automaton which recognizes the word "ab"
   * (Character 'a', (Character 'b' (Match)))
   */
  Automaton a;
  a.type = Character;
  a.symbol = 'a';
  a.next = std::make_shared<Automaton>(Character, 'b');
  a.next->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.IsDeterministic() == true,
      "Automaton for word 'ab' is deterministic");
}

void TestWordWithEmpty() {
  /*
   * An automaton which ends with the Empty automaton
   * (Character 'a' (Character 'b' (Empty)))
   */
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Character, 'b');
  a.next->next = std::make_shared<Automaton>(Empty, '\0');
  T::okay(a.IsDeterministic() == true,
      "Automaton which ends with the Empty automaton is deterministic");
}

void TestWordWithSplit() {
  /*
   * An automaton which recognizes the regex a(b|c)
   * (Character 'a' (Split (Character 'b' (Match)) (Character 'c' (Match))))
   */
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Split, '\0');
  a.next->next = std::make_shared<Automaton>(Character, 'b');
  a.next->next->next = std::make_shared<Automaton>(Match, '\0');
  a.next->nextSplit = std::make_shared<Automaton>(Character, 'c');
  a.next->next->nextSplit = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.IsDeterministic() == false,
      "Automaton with Split isn't determministic");
}

void TestWordWithDeeperSplit() {
  /*
   * An automaton which recognizes the regex abc((ba|a)|c)
   * (Character 'a' (Character 'b' (Character 'c'
   *   (Split
   *     (Split (Character 'b' (Character 'a' (Match))) (Character 'a' (Match)))
   *     (Character 'c' (Match))))))
   */
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Character, 'b');
  a.next->next = std::make_shared<Automaton>(Character, 'c');
  a.next->next->next = std::make_shared<Automaton>(Split, '\0');
  a.next->next->next->next = std::make_shared<Automaton>(Split, '\0');
  a.next->next->next->next->next = std::make_shared<Automaton>(Character, 'b');
  a.next->next->next->next->next->next = std::make_shared<Automaton>(Character, 'a');
  a.next->next->next->next->next->next->next = std::make_shared<Automaton>(Match, '\0');
  a.next->next->next->next->nextSplit = std::make_shared<Automaton>(Character, 'a');
  a.next->next->next->next->nextSplit->next = std::make_shared<Automaton>(Match, '\0');
  a.next->next->next->nextSplit = std::make_shared<Automaton>(Character, 'c');
  a.next->next->next->nextSplit->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.IsDeterministic() == false,
      "Automaton with deep Split isn't determministic");
}

int main() {
  std::cout << "Testing IsDeterministic on automaton\n";

  TestWordAB();
  TestWordWithEmpty();
  TestWordWithSplit();
  TestWordWithDeeperSplit();

  return 0;
}
