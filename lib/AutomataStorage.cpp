#include "AutomataStorage.h"
#include "Automaton.h"

#include <iostream>
#include <limits>
#include <cassert>


size_t AutomataStorage::Add(std::shared_ptr<Automaton> automatonToAdd) {
  assert(std::numeric_limits<size_t>::max() > currentIdentifier);

  currentIdentifier++;
  automatons.insert(std::make_pair(currentIdentifier, automatonToAdd));

  return currentIdentifier;
}

const std::shared_ptr<Automaton> AutomataStorage::Retrieve(size_t idToRetrieve) const {
  auto automatonIter = automatons.find(idToRetrieve);
  if (automatonIter != automatons.end()) {
    return automatonIter->second;
  }
  return nullptr;
}

void AutomataStorage::PrintAll() const {
  for (auto a : automatons) {
    a.second->Print();
  }
}
