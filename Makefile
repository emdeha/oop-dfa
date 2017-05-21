all: main.out ./lib/Automaton.h ./lib/AutomataStorage.h
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror -o main.out main.cpp \
		./lib/Automaton.cpp ./lib/AutomataStorage.cpp
