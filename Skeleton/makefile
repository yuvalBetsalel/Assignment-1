# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: main

main: clean bin/main.o bin/Auxiliary.o bin/Facility.o bin/Settlement.o bin/SelectionPolicy.o bin/Plan.o
	g++ -o bin/main bin/main.o bin/Auxiliary.o bin/Facility.o bin/Settlement.o bin/SelectionPolicy.o bin/Plan.o

bin/main.o: src/main.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Auxiliary.o: src/Auxiliary.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp

bin/Facility.o: src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp

bin/Settlement.o: src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp

bin/SelectionPolicy.o: src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp

bin/Plan.o: src/Plan.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Plan.o src/Plan.cpp

clean: 
	rm -f bin/*

run: main
	./bin/main