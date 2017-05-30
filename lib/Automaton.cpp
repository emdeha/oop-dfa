#include "./Automaton.h"

#include <iostream>
#include <string>


/*
 * An automaton's language is empty if the automaton only recognizes the empty
 * word.
 * This can happen when either there's a single Match node, or there are only
 * Split nodes because they represent epsilon-transitions.
 */
// TODO: Track whether there's a cycle in the automaton
bool Automaton::IsEmpty() const {
  if (type == Match) { return true; }
  if (type == Split) {
    return next->IsEmpty() && nextSplit->IsEmpty();
  }

  return false;
}

/*
 * The current data structure represents an automaton which is always
 * non-deterministic if it has a Split node.
 */
// TODO: Track whether there's a cycle in the automaton
bool Automaton::IsDeterministic()  const {
  if (next == nullptr) {
    return true;
  }

  if (type == Split) {
    return false;
  }

  return next->IsDeterministic();
}

bool Automaton::Recognize(std::string word) const {
  auto next = this;
  switch (next->type) {
    case Match: return true;
    case Character:
      if (!next->next) { return false; }
      return word[0] == symbol ? next->next->Recognize(word.substr(1))
                               : false;
    case Split: return false;
    default: return false;
  }
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
  }

  serial += ")";
  return serial;
}
