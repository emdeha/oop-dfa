all: main.out
	clang++ -std=c++11 -Wall -Wpedantic -Wextra -Werror -o main.out main.cpp
