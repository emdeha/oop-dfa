#include "AutomataStorage.h"
#include "Automaton.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <streambuf>


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

void AutomataStorage::SaveAutomaton(size_t id, const std::string &filename) const {
  auto automaton = Retrieve(id);
  if (automaton) {
    // TODO: Check if the file was open successfully
    std::ofstream saveFile(filename);
    saveFile << automaton->ToJson();
    return;
  }

  // TODO: Maybe it's not a good idea for a library to use stdout
  std::cout << "No automaton specified by the given id\n";
}

size_t AutomataStorage::LoadAutomaton(const std::string &filename) {
  auto a = std::make_shared<Automaton>();
  std::ifstream loadFile(filename);
  std::string serial((std::istreambuf_iterator<char>(loadFile)),
                      std::istreambuf_iterator<char>());
  a->FromJson(serial);
  return Add(a);
}
