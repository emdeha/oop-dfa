test: main
	./t/make.sh && ./t/test.sh

main: main.cpp ./lib/Automaton.h ./lib/AutomataStorage.h
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror -o main.out \
		main.cpp ./lib/Automaton.cpp ./lib/AutomataStorage.cpp ./lib/InteractiveConsole.cpp

clean:
	rm -f main.out t/**/*.test.out
	rm -f ./**/test.dfa
