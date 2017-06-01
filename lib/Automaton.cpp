#include "./Automaton.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/*
 * An automaton's language is empty if the automaton only recognizes the empty
 * word.
 * This can happen when either there's a single Match node, or there are only
 * Split nodes because they represent epsilon-transitions.
 */
// TODO: Track whether there's a cycle in the automaton
bool Automaton::IsEmpty() const {
  if (type == Match) { return true; }
  if (type == Split) {
    return next->IsEmpty() && nextSplit->IsEmpty();
  }

  return false;
}

/*
 * The current data structure represents an automaton which is always
 * non-deterministic if it has a Split node.
 */
// TODO: Track whether there's a cycle in the automaton
bool Automaton::IsDeterministic()  const {
  if (next == nullptr) {
    return true;
  }

  if (type == Split) {
    return false;
  }

  return next->IsDeterministic();
}

void Automaton::AddState(AutomatonConstPtr state, StatesList &list) const {
  // TODO: Optimize check for whether the state was already added
  if (!state ||
      // Don't put duplicate states
      std::find(list.begin(), list.end(), state) != list.end()) {
    return;
  }

  if (state->type == Split) {
    AddState(state->next, list);
    AddState(state->nextSplit, list);
    return;
  }

  list.push_back(state);
}

bool Automaton::Recognize(std::string word) const {
  AddState(std::make_shared<Automaton>(*this), currentStates);

  for (char &c: word) {
    for (auto state: currentStates) {
      if (state->type == Character && state->symbol == c) {
        AddState(state->next, nextStates);
      }
    }
    currentStates.swap(nextStates);
    nextStates.clear();
  }

  for (auto state: currentStates) {
    if (state->type == Match) {
      return true;
    }
  }
  return false;
}

std::string Automaton::ToSerial() const {
  std::string serial = "(";

  switch (type) {
    case Character:
      serial += "Character '";
      serial += symbol;
      serial += "'";
      if (next) {
        serial += " ";
        serial += next->ToSerial();
      }
      break;
    case Split:
      if (!next) {
        serial += "Split () ";
      } else {
        serial += "Split ";
        serial += next->ToSerial();
        serial += " ";
      }

      if (!nextSplit) {
        serial += "()";
      } else {
        serial += nextSplit->ToSerial();
      }
      break;
    case Match:
      serial += "Match";
      break;
  }

  serial += ")";
  return serial;
}


/*
 * We use an S-expression grammar to store the Automaton.
 * automaton ::= '(' <character> | <split> | <match> ')'
 * character ::= "Character" <char> <automaton>
 * char ::= [a-z0-9]
 * split ::= "Split" <automaton> <automaton>
 * match ::= "Match"
 */
/*
enum TokenType {
  LParen,
  RParen,
  Character,
  Split,
  Match
}

struct Token {
  TokenType type;
  char symbol;

  Token(TokenType _type)
    : type(_type) {}

  Token(TokenType _type, char _symbol)
    : type(_type), symbol(_symbol) {}
}

std::string ExtractWordFrom(size_t &from, const std::string &str) {
  size_t to = str.find_first_of(' ', from);
  std::string extracted = str.substr(from, to);
  from = to;
  return extracted;
}

std::vector<Token> Tokenize(const std::string &serial) {
  std::vector tokens;
  size_t i = 0;

  while (serial[i]) {
    char c = serial[i];
    if (c == '(') {
      tokens.push_back(Token(LParen));
      i++;
    } else if (c == ')') {
      tokens.push_back(Token(RParen));
      i++;
    } else if (c == ' ') {
      i++;
    } else {
      std::string word = ExtractWordFrom(&i, serial);
      if (word == "Character") {
        // Read <char>
        i++;
        char character = ExtractWordFrom(i, serial);
        tokens.push_back(Token(Character, character));
      } else if (word == "Split") {
        tokens.push_back(Token(Split));
        i++;
      } else if (word == "Match") {
        tokens.push_back(Token(Match));
        i++;
      } else {
        std::cout << "Invalid word: " << word << "\n";
        return;
      }
    }
  }
}

std::pair<AutomatonConstPtr, std::vector<Token>>
ParseAutomaton(const std::vector<Token> &tokens) {
}

std::pair<AutomatonConstPtr, std::vector<Token>>
ParseCharacter(const std::vector<Token> &tokens) {
}

std::pair<AutomatonConstPtr, std::vector<Token>>
ParseSplit(const std::vector<Token> &tokens) {
}

std::pair<AutomatonConstPtr, std::vector<Token>>
ParseMatch(const std::vector<Token> &tokens) {
}
*/

void Automaton::FromSerial(const std::string &serial) {
  // Remove old data
  type = Match;
  symbol = '\0';
  next = nullptr;
  nextSplit = nullptr;

  // Deserialize
  std::cout << serial;
  auto tokens = Tokenize(serial);
  auto parsed = ParseAutomaton(tokens);
  /*
  if (parsed.rest) {
    std::cout << "Leftover tokens: ";
    for (auto t: tokens) {
      std::cout << t.ToString();
    }
    std::cout << "\n";
    return;
  }
  */

  this = *(parsed.first);
}
