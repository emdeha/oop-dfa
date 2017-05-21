// #define NDEBUG
#include <iostream>
#include <memory>

#include "lib/Automaton.h"
#include "lib/AutomataStorage.h"


int main() 
{
  std::cout << "Hello world!\n";

  AutomataStorage as = AutomataStorage();
  as.Add(std::make_shared<Automaton>(Automaton(1)));
  as.Add(std::make_shared<Automaton>(Automaton(2)));
  as.Add(std::make_shared<Automaton>(Automaton(3)));
  as.Add(std::make_shared<Automaton>(Automaton(4)));

  for (size_t i = 1; i <= 4; ++i) {
    auto a = as.Retrieve(i);
    if (a) {
      a->Print();
    }
  }

  return 0;
}
