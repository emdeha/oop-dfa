#include "./Automaton.h"

#include <iostream>
#include <string>


bool Automaton::IsEmpty() const {
  return type == Empty;
}

/*
 * The current data structure represents an automaton which is always
 * non-deterministic if it has a Split node.
 */
bool Automaton::IsDeterministic()  const {
  if (next == nullptr) {
    return true;
  }

  if (type == Split) {
    return false;
  }

  return next->IsDeterministic();
}
