#pragma once

#include <map>
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

  public:
    void List() const;

    // TODO: Make private once you've implemented loading from file
    size_t Add(std::shared_ptr<Automaton> automatonToAdd);
    const std::shared_ptr<Automaton> Retrieve(size_t idToRetrieve) const;

    void PrintAll() const;
};
