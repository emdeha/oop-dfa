#pragma once

#include <memory>
#include <vector>
#include "json.hpp"


enum AutomatonType {
  Character, Split, Match, Invalid = -1
};


class AutomataStorage;
class Automaton;

// TODO: Consider using weak_ptr because of possible circular deps
typedef std::shared_ptr<Automaton> AutomatonPtr;
typedef std::shared_ptr<const Automaton> AutomatonConstPtr;
typedef std::pair<AutomatonPtr, AutomatonPtr> AutomatonPair;
typedef std::vector<AutomatonConstPtr> StatesList;

/*
 * The following automaton data structure realization is largely influenced by
 * https://swtch.com/~rsc/regexp/regexp1.html
 */
class Automaton {
#ifndef DFA_TESTING
  private:
#else
  public:
#endif
    AutomatonType type;
    char symbol;
    AutomatonPtr next;
    AutomatonPtr nextSplit;

    // These lists are used by the matching algorithm
    mutable StatesList currentStates;
    mutable StatesList nextStates;

    void AddState(AutomatonConstPtr, StatesList&) const;

    void FromJsonHelper(const nlohmann::json&);

  public:
    Automaton()
      : type(Match), symbol('\0'), next(nullptr), nextSplit(nullptr) {}
    Automaton(AutomatonType _type, char _symbol)
      : type(_type), symbol(_symbol), next(nullptr), nextSplit(nullptr) {}

    // Used for debugging purposes
    std::string ToString() const;
    nlohmann::json ToJson() const;
    void FromJson(const std::string&);

    bool IsEmpty() const;
    bool IsDeterministic() const;

    bool Recognize(std::string word) const;
};
