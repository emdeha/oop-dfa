#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"


void TestRecognizeEmptyWord() {
  Automaton a(Match, '\0');
  T::okay(a.Recognize("") == true,
      "Recognizes the lonely empty word");
  T::okay(a.Recognize("abc") == true,
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
  T::okay(a.Recognize("ab") == true,
      "Doesn't recognize half-word");
  T::okay(a.Recognize("") == false,
      "Doesn't recognize the empty word");
}

void TestRecognizeOneLevelSplitWords() {
  // Recognizes "a(a|c)b"
  // (Character 'a' (Split
  //   (Character 'a' (Character 'b' (Match)))
  //   (Character 'c' (Character 'b' (Match)))))
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Split, '\0');
  a.next->next = std::make_shared<Automaton>(Character, 'a');
  a.next->nextSplit = std::make_shared<Automaton>(Character, 'c');
  auto lastA = std::make_shared<Automaton>(Character, 'b');
  lastA->next = std::make_shared<Automaton>(Match, '\0');
  a.next->next->next = lastA;
  a.next->nextSplit->next = lastA;
  T::okay(a.Recognize("abb") == true,
      "Recognizes first alternation");
  T::okay(a.Recognize("acb") == true,
      "Recognizes second alternation");
  T::okay(a.Recognize("ac") == true,
      "Doesn't recognize only first two characters");
  T::okay(a.Recognize("ab") == true,
      "Doesn't recognize first and last character only");
  T::okay(a.Recognize("") == false,
      "Doesn't recognize the empty word");
}

void TestRecognizeMultiLevelSplitWords() {
  // Recognizes "a(ab|(c|d))d"
  // (Character 'a' (Split
  //   (Character 'a' (Character 'b' (Character 'd' (Match))))
  //   (Split (Character 'c' (Character 'd' (Match)))
  //          (Character 'd' (Character 'd' (Match))))))
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Split, '\0');
  a.next->next = std::make_shared<Automaton>(Character, 'a');
  a.next->next->next = std::make_shared<Automaton>(Character, 'b');
  a.next->nextSplit = std::make_shared<Automaton>(Split, '\0');
  a.next->nextSplit->next = std::make_shared<Automaton>(Character, 'c');
  a.next->nextSplit->nextSplit = std::make_shared<Automaton>(Character, 'd');
  auto lastA = std::make_shared<Automaton>(Character, 'd');
  lastA->next = std::make_shared<Automaton>(Match, '\0');
  a.next->next->next->next = lastA;
  a.next->nextSplit->next = lastA;
  a.next->nextSplit->nextSplit = lastA;
  T::okay(a.Recognize("aabd") == true,
      "Recognizes first alternative");
  T::okay(a.Recognize("acd") == true,
      "Recognizes second alternative");
  T::okay(a.Recognize("add") == true,
      "Recognizes third alternative");
  T::okay(a.Recognize("aab") == false,
      "Doesn't recognize half spit");
  T::okay(a.Recognize("aad") == false,
      "Doesn't recognize other half split");
  T::okay(a.Recognize("ad") == false,
      "Doesn't recognize first and last character only");
  T::okay(a.Recognize("") == false,
      "Doesn't recognize the empty word");
}
   
void TestRecognizeMultipleSplitWords() {
  // Recongnizes "a(a|b)cd(e|(f|d))"
  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Split, '\0');
  a.next->next = std::make_shared<Automaton>(Character, 'a');
  a.next->nextSplit = std::make_shared<Automaton>(Character, 'b');
  auto halfA = std::make_shared<Automaton>(Character, 'c');
  halfA->next = std::make_shared<Automaton>(Character, 'd');
  halfA->next->next = std::make_shared<Automaton>(Split, '\0');
  halfA->next->next->next = std::make_shared<Automaton>(Character, 'e');
  halfA->next->next->nextSplit = std::make_shared<Automaton>(Split, '\0');
  halfA->next->next->nextSplit->next = std::make_shared<Automaton>(Character, 'f');
  halfA->next->next->nextSplit->nextSplit = std::make_shared<Automaton>(Character, 'd');
  a.next->next->next = halfA;
  a.next->next->nextSplit = halfA;
  T::okay(a.Recognize("aacde") == true,
      "Recognizes first alternation");
  T::okay(a.Recognize("abcde") == true,
      "Recognizes second alternation");
  T::okay(a.Recognize("aacdf") == true,
      "Recognizes third alternation");
  T::okay(a.Recognize("abcdf") == true,
      "Recognizes fourth alternation");
  T::okay(a.Recognize("aacdd") == true,
      "Recognizes fifth alternation");
  T::okay(a.Recognize("abcdd") == true,
      "Recognizes sixth alternation");
  T::okay(a.Recognize("acd") == false,
      "Doesn't recognize word without alternations");
  T::okay(a.Recognize("aef") == false,
      "Doesn't recognize word only of alternations");
  T::okay(a.Recognize("") == false,
      "Doesn't recognize the empty word");
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
