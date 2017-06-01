#pragma once

#include <map>
#include <vector>
#include <memory>


class Automaton;

class AutomataStorage {
#ifndef DFA_TESTING
  private:
#else
  public:
#endif
    std::map<size_t, std::shared_ptr<Automaton>> automatons;
    size_t currentIdentifier;

    size_t Add(std::shared_ptr<Automaton> automatonToAdd);
    std::shared_ptr<const Automaton> Retrieve(size_t) const;

  public:
    std::vector<size_t> List() const;

    void SaveAutomaton(size_t, const std::string&) const;
    void LoadAutomaton(const std::string&);
};
