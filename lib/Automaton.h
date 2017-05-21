#pragma once

class Automaton {
  private:
    int testIdentifier;

  public:
    Automaton() {}

    Automaton(int id)
      : testIdentifier(id) {}

    void Print();
};
