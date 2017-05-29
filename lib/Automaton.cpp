#include "./Automaton.h"

#include <iostream>
#include <string>


bool Automaton::IsEmpty() const {
  return type == Empty;
}
