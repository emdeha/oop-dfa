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

bool Automaton::Recognize() const {
  return false;
}

std::string Automaton::ToSerial() const {
  std::string serial = "(";

  switch (type) {
    case Character:
      serial += "Character '";
      serial += symbol;
      serial += "' ";
      if (next) {
        serial += next->ToSerial();
      }
      break;
    case Split:
      if (!next) {
        serial += "Split ()";
      } else {
        serial += "Split ";
        serial += next->ToSerial();
        serial += " ";
      }

      if (!nextSplit) {
        serial += "()";
      } else {
        serial += nextSplit->ToSerial();
      }
      break;
    case Match:
      serial += "Match";
      break;
    case Empty:
      serial += "Empty";
      break;
  }

  serial += ")";
  return serial;
}
