V Implement automaton serialization

2. Implement basic automaton methods
  2.1. Public
    V `isEmpty` -- checks whether an automaton is empty
    V `isDeterministic` -- checks whether an automaton is deterministic
    V `recognize` -- checks wheter the automaton recognizes a word from its
    language

V Implement `AutomataStorage` serialization
  - `load` -- loads an automaton for a file and puts it in the storage
  - `save` -- saves an automaton to a file, given its id

4. Implement `AutomataStorage` automata operations
  - `withConcat` -- given two automata ids, concatenates the two automata
  in a new automaton; returns the automaton id
  - `withUnion` -- given two automata ids, unions the two automata in a new
  automaton; returns the automaton id
  - `withUn` -- given an automaton, creates an automaton which is the positive
  cover of the given automaton; returns the new automaton id
  - `fromRegex` -- creates an automaton from a regular expression; returns its
  id

5. Implement interactive console

6. Polishing
  - Implement an error-handling mechanism
  - Fix all possible cycles in the automaton
