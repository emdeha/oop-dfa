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
    case Invalid:
      std::cout << "Error: Invalid char\n";
      return "INVALID";
  }

  serial += ")";
  return serial;
}

std::string AutomatonTypeToString(AutomatonType t) {
  switch (t) {
    case Character: return "Character";
    case Split: return "Split";
    case Match: return "Match";
    case Invalid:
      std::cout << "Error: No such automaton type" << t << "\n";
      return "INVALID";
    default:
      std::cout << "Error: No such automaton type" << t << "\n";
      return "INVALID";
  }
}

AutomatonType AutomatonTypeFromString(const std::string &str) {
  if (str == "Character") {
    return Character;
  } else if (str == "Split") {
    return Split;
  } else if (str == "Match") {
    return Match;
  }

  std::cout << "Error: No such automaton type" << str << "\n";
  return Invalid;
}

nlohmann::json Automaton::ToJson() const {
  nlohmann::json j;
  j["type"] = AutomatonTypeToString(type);
  j["symbol"] = symbol;
  // TODO: Check for cycles if implementing Kleene star or other infinite
  // automaton structs
  if (next) {
    j["next"] = next->ToJson();
  }
  if (nextSplit) {
    j["nextSplit"] = nextSplit->ToJson();
  }
  return j;
}

void Automaton::FromJsonHelper(const nlohmann::json& j) {
  type = AutomatonTypeFromString(j["type"]);
  int symbolCode = j["symbol"];
  symbol = static_cast<char>(symbolCode);
  if (j.find("next") != j.end()) {
    auto nextA = std::make_shared<Automaton>();
    nextA->FromJsonHelper(j["next"]);
    next = nextA;
  }
  if (j.find("nextSplit") != j.end()) {
    auto nextA = std::make_shared<Automaton>();
    nextA->FromJsonHelper(j["nextSplit"]);
    nextSplit = nextA;
  }
}

void Automaton::FromJson(const std::string& str) {
  nlohmann::json j = nlohmann::json::parse(str);
  FromJsonHelper(j);
}

void Automaton::FromAutomaton(const Automaton &a) {
  type = a.type;
  symbol = a.symbol;
  if (a.next) {
    next = std::make_shared<Automaton>();
    next->FromAutomaton(*a.next);
  }

  if (a.nextSplit) {
    nextSplit = std::make_shared<Automaton>();
    nextSplit->FromAutomaton(*a.nextSplit);
  }
}

void Automaton::ReplaceMatchingStates(AutomatonPtr a) {
  if (type == Match) {
    type = a->type;
    symbol = a->symbol;
    next = a->next;
    nextSplit = a->nextSplit;
    return;
  }

  if (next) {
    next->ReplaceMatchingStates(a);
  }

  if (nextSplit) {
    nextSplit->ReplaceMatchingStates(a);
  }
}
