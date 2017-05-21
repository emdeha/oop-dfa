1. Implement automaton serialization
	- Use S-expressions -- http://www.buildyourownlisp.com/chapter9_s_expressions
	- Structure
	```c++
	class Automaton {
	  enum type = { Character, Match, Split };
		char symbol;
		std::shared_ptr<Automaton> next;
		std::shared_ptr<Automaton> nextSplit;
	};
	```

2. Implement basic automaton methods
	2.1. Public
		- `isEmpty` -- checks whether an automaton is empty
		- `isDeterministic` -- checks whether an automaton is deterministic
		- `recognize` -- checks wheter the automaton recognizes a word from its
		language

3. Implement `AutomataStorage` serialization
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
