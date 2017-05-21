#!/bin/bash
cd `dirname $0`

for f in **/*.test.cpp
do
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror \
		-o $(sed s/cpp$/out/ <(echo ${f})) ${f} \
		../lib/AutomataStorage.cpp ../lib/Automaton.cpp
done
