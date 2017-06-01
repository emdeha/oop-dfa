#include "./Automaton.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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

void Automaton::AddState(AutomatonConstPtr state, StatesList &list) const {
  // TODO: Optimize check for whether the state was already added
  if (!state ||
      // Don't put duplicate states
      std::find(list.begin(), list.end(), state) != list.end()) {
    return;
  }

  if (state->type == Split) {
    AddState(state->next, list);
    AddState(state->nextSplit, list);
    return;
  }

  list.push_back(state);
}

bool Automaton::Recognize(std::string word) const {
  AddState(std::make_shared<Automaton>(*this), currentStates);

  for (char &c: word) {
    for (auto state: currentStates) {
      if (state->type == Character && state->symbol == c) {
        AddState(state->next, nextStates);
      }
    }
    currentStates.swap(nextStates);
    nextStates.clear();
  }

  for (auto state: currentStates) {
    if (state->type == Match) {
      return true;
    }
  }
  return false;
}

std::string Automaton::ToString() const {
  std::string serial = "(";

  switch (type) {
    case Character:
      serial += "Character '";
      serial += symbol;
      serial += "'";
      if (next) {
        serial += " ";
        serial += next->ToString();
      }
      break;
    case Split:
      if (!next) {
        serial += "Split () ";
      } else {
        serial += "Split ";
        serial += next->ToString();
        serial += " ";
      }

      if (!nextSplit) {
        serial += "()";
      } else {
        serial += nextSplit->ToString();
      }
      break;
    case Match:
      serial += "Match";
      break;
  }

  serial += ")";
  return serial;
}
