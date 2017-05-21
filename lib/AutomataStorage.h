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
    std::shared_ptr<const Automaton> Retrieve(size_t idToRetrieve) const;

  public:
		// TODO: Use a const_iterator view to retrieve the automata and prevent
		// the user from modifying them
		std::map<size_t, std::shared_ptr<Automaton>> List() const;
};
