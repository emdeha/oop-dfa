// #define NDEBUG
#include <iostream>
#include <memory>
#include <string>

#include "lib/Automaton.h"
#include "lib/AutomataStorage.h"
#include "lib/InteractiveConsole.h"


int main() 
{
  AutomataStorage as;
  InteractiveConsole ic;

  // Main commands
  ic.AddCommand("Open", 1, [&ic, &as](ArgVector args) {
    auto filename = args[0];
    std::cout << "Loading automaton from " << filename << "\n";
    as.LoadAutomaton(filename);
    ic.AcceptOtherCommands(filename);
  });
  ic.AddCommand("Close", 0, [&ic](ArgVector) {
    ic.StopAcceptingOtherCommands();
  });
  ic.AddCommand("Save", 1, [&ic, &as](ArgVector args) {
    auto id = args[0];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    auto filename = ic.GetCurrentFile();
    if (filename.size() > 0) {
      as.SaveAutomaton(properId, filename);
    } else {
      std::cout << "No file opened\n";
    }
  });
  ic.AddCommand("SaveAs", 2, [&as](ArgVector args) {
    auto id = args[0];
    auto filename = args[1];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    as.SaveAutomaton(properId, filename);
  });
  ic.AddCommand("Exit", 0, [&ic](ArgVector) {
    ic.Stop();
  });
  ic.AddCommand("Help", 0, [&ic](ArgVector) {
    ic.ListCommands();
  });
  ic.SetMainCommands({ "Open", "Close", "Save", "SaveAs", "Exit", "Help" });

  // Project-specific commands
  ic.AddCommand("List", 0, [&as](ArgVector) {
    auto indexes = as.List();
    if (indexes.size() <= 0) {
      std::cout << "No automatons\n";
      return;
    }

    std::cout << "Automatons with indexes: ";
    for (auto i: indexes) {
      std::cout << i;
    }
    std::cout << "\n";
  });

  ic.AddCommand("Print", 1, [&as](ArgVector args) {
    auto id = args[0];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    auto a = as.Retrieve(properId);
    std::cout << a->ToString() << "\n";
  });

  ic.AddCommand("Empty", 1, [&as](ArgVector args) {
    auto id = args[0];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    auto a = as.Retrieve(properId);
    std::cout << a->IsEmpty() << "\n";
  }); 

  ic.AddCommand("Deterministic", 1, [&as](ArgVector args) {
    auto id = args[0];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    auto a = as.Retrieve(properId);
    std::cout << a->IsDeterministic() << "\n";
  });

  ic.AddCommand("Recognize", 2, [&as](ArgVector args) {
    auto id = args[0];
    auto word = args[1];
    size_t properId = InteractiveConsole::ArgToSizeT(id);
    auto a = as.Retrieve(properId);
    std::cout << a->Recognize(word) << "\n";
  });

  // Run the interactive console
  ic.Loop();
  
  return 0;
}
