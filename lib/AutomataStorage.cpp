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

std::shared_ptr<const Automaton> AutomataStorage::Retrieve(size_t idToRetrieve) const {
  auto automatonIter = automatons.find(idToRetrieve);
  if (automatonIter != automatons.end()) {
    return automatonIter->second;
  }
  return nullptr;
}

std::vector<size_t> AutomataStorage::List() const {
  std::vector<size_t> automataIndexes;
  for (auto a : automatons) {
    automataIndexes.push_back(a.first);
  }
  return automataIndexes;
}
