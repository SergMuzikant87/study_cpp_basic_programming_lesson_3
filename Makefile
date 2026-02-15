CC := g++
FLAGS := -Wall -O2 -std=c++11 -g

build:
	$(CC) $(FLAGS) source/programm_1.cpp -o output/programm_1
	$(CC) $(FLAGS) source/programm_2.cpp -o output/programm_2
