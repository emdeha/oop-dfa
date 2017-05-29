#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"


void TestRecognizeEmptyWord() {
  Automaton a(Empty, '\0');
  T::okay(a.Recognize("\0") == true,
      "Recognizes the lonely empty word");
  T::okay(a.Recognize("\0abc") == true,
      "Recognizes the empty word with trailing letters");
}

void TestRecognizeNoSplitWords() {
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Character, 'b');
  a.next->next = std::make_shared<Automaton>(Character, 'c');
  a.next->next->next = std::make_shared<Automaton>(Character, 'd');
  T::okay(a.Recognize("abcd") == false,
      "Doesn't recognize word without a Match at the end");
  a.next->next->next->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.Recognize("abcd") == true,
      "Recognizes word with Match at the end");
  a.next->next->next->next = std::make_shared<Automaton>(Empty, '\0');
  T::okay(a.Recognize("abcd") == false,
      "Doesn't recognize word with Empty at the end");
  a.next->next->next->next->next = std::make_shared<Automaton>(Empty, '\0');
  a.next->next->next->next->next->next = std::make_shared<Automaton>(Match, '\0');
  T::okay(a.Recognize("abcd") == true,
      "Recognizes word with Empty before the Match");
  T::okay(a.Recognize("ab") == true,
      "Doesn't recognize half-word");
}

void TestRecognizeOneLevelSplitWords() {
}

void TestRecognizeMultiLevelSplitWords() {
}
   
void TestRecognizeMultipleSplitWords() {
}

int main() {
  std::cout << "Testing Recognize on automaton\n";

  std::cout << "  Recognize the empty word\n";
  TestRecognizeEmptyWord();

  std::cout << "  Recognizes words without splits\n";
  TestRecognizeNoSplitWords();

  std::cout << "  Recognizes words with one-level splits\n";
  TestRecognizeOneLevelSplitWords();

  std::cout << "  Recognizes words with multi-level splits\n";
  TestRecognizeMultiLevelSplitWords();
   
  std::cout << "  Recognizes words with mutliple splits\n";
  TestRecognizeMultipleSplitWords();

  return 0;
}
