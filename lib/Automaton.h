#pragma once

#include <memory>


enum AutomatonType {
  Character, Split, Match, Empty 
};

/*
 * The following automaton data structure realization is largely influenced by
 * https://swtch.com/~rsc/regexp/regexp1.html
 */
class Automaton {
#ifndef DFA_TESTING
  private:
#else
  public:
#endif
    typedef std::shared_ptr<Automaton> AutomatonPtr;
    typedef std::pair<AutomatonPtr, AutomatonPtr> AutomatonPair;
    AutomatonType type;
    char symbol;
    std::shared_ptr<Automaton> next;
    std::shared_ptr<Automaton> nextSplit;

    /*
     * We use an S-expression grammar to store the Automaton.
     * automaton ::= '(' <character> | <split> | <match> | <empty> ')'
     * character ::= "Character" <char> <automaton>
     * char ::= [a-z0-9]
     * split ::= "Split" <automaton> <automaton>
     * match ::= "Match"
     * empty ::= "Empty"
     */
    void Parse(std::string, int);
    AutomatonPtr ParseCharacter(std::string, int);
    AutomatonPair ParseSplit(std::string, int);

  public:
    Automaton()
      : type(Empty), symbol('\0'), next(nullptr), nextSplit(nullptr) {}
    Automaton(AutomatonType _type, char _symbol)
      : type(_type), symbol(_symbol), next(nullptr), nextSplit(nullptr) {}

    std::string ToSerial() const;
    void FromSerial(std::string);

    bool IsEmpty() const;
    bool IsDeterministic() const;
};
