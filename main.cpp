#include <iostream>

#include "lib/AutomataStorage.h"
#include "lib/Automaton.h"


int main() 
{
  std::cout << "Hello world!\n";

  Automaton a = Automaton();
  AutomataStorage as = AutomataStorage();

  a.Print();
  as.Print();

  return 0;
}
