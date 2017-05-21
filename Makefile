main: main.cpp ./lib/Automaton.h ./lib/AutomataStorage.h
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror -o main.out main.cpp \
		./lib/Automaton.cpp ./lib/AutomataStorage.cpp

test: ./t/test.cpp
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror -o t/test.out t/test.cpp
	./t/test.out

clean:
	rm -f main.out t/test.out
