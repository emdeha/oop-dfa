#pragma once

class Automaton {
#ifndef DFA_TESTING
  private:
#else
	public:
#endif
    int testIdentifier;

  public:
    Automaton() {}

    Automaton(int id)
      : testIdentifier(id) {}

    void Print();
};
