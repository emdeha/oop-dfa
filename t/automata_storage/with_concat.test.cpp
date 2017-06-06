#include <iostream>

#define DFA_TESTING
#include "../Test.h"
#include "../../lib/Automaton.h"
#include "../../lib/AutomataStorage.h"


void TestConcatTwoLinearAutomatons() {
  std::cout << "  Testing concat of simple linear automatons\n";
  AutomataStorage as;

  Automaton a(Character, 'a');
  a.next = std::make_shared<Automaton>(Character, 'b');
  a.next->next = std::make_shared<Automaton>(Match, '\0');
  size_t aId = as.Add(std::make_shared<Automaton>(a));

  Automaton b(Character, 'c');
  b.next = std::make_shared<Automaton>(Match, '\0');
  size_t bId = as.Add(std::make_shared<Automaton>(b));

  size_t cId = as.WithConcat(aId, bId);
  auto c = as.Retrieve(cId); 

  T::okay(c->type == Character && c->symbol == 'a',
      "First state is the first state of 'a'");
  T::okay(c->next->type == Character && c->next->symbol == 'b',
      "Second state is the second state of 'a'");
  T::okay(c->next->next->type == Character && c->next->next->symbol == 'c',
      "Third state is the first state of 'b'");
  T::okay(c->next->next->next->type == Match,
      "Fourth state is the matching state of 'b'");

  std::cout << "  Testing concat of an automaton which begins with a final state\n";
  Automaton d(Match, '\0');
  size_t dId = as.Add(std::make_shared<Automaton>(d));
  size_t eId = as.WithConcat(dId, bId);
  auto e = as.Retrieve(eId);

  T::okay(e->type == Character && e->symbol == 'c',
      "First state is the first state of 'b'");
  T::okay(e->next->type == Match,
      "Second state is the last state of 'b'");
}

void TestConcatTwoSplitAutomatons() {
  AutomataStorage as;

  auto a = std::make_shared<Automaton>(Character, 'a');
  a->next = std::make_shared<Automaton>(Split, '\0');
  a->next->next = std::make_shared<Automaton>(Character, 'b');
  a->next->next->next = std::make_shared<Automaton>(Match, '\0');
  a->next->nextSplit = std::make_shared<Automaton>(Match, '\0');
  size_t aId = as.Add(a);

  auto b = std::make_shared<Automaton>(Character, 'b'); 
  b->next = std::make_shared<Automaton>(Match, '\0');
  size_t bId = as.Add(b);

  size_t cId = as.WithConcat(aId, bId);
  auto c = as.Retrieve(cId);

  T::okay(c->type == Character && c->symbol == 'a',
      "First state of 'c' is the first state of 'a'");
  T::okay(c->next->type == Split,
      "Second state of 'c' is the second state of 'a'");
  T::okay(c->next->next->type == Character && c->next->next->symbol == 'b',
      "Third state of 'c' is the first split state of 'a'");
  auto fourthState = c->next->next->next;
  T::okay(fourthState->type == Character && fourthState->symbol == 'b',
      "Fourth state of 'c' is the first state of 'b'");
  auto fifthState = c->next->next->next->next;
  T::okay(fifthState->type == Match,
      "Fifth state of 'c' is the final state of 'b'");
  auto sixthState = c->next->nextSplit;
  T::okay(sixthState->type == Character && sixthState->symbol == 'b',
      "Sixth state of 'c' is the first state of 'b'");
  auto seventhState = c->next->nextSplit->next;
  T::okay(seventhState->type == Match,
      "Seventh state of 'c' is the final state of 'b'");
}

int main() {
  std::cout << "Testing automaton concatenation\n";

  TestConcatTwoLinearAutomatons();
  TestConcatTwoSplitAutomatons();

  return 0;
}
