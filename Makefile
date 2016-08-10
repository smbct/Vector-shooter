EXEC=shooter

CC=g++
CXX=g++
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

OPTIONS=-std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter

.PHONY = clean

OBJECTS_FILES = main.o TextureManager.o Game.o Entity.o EntityManager.o PlayerController.o

gcc : CXXFLAGS= $(OPTIONS) -O3
gcc : main

gcc-debug : CXXFLAGS=$(OPTIONS) -ggdb
gcc-debug : main

run :
	./main

debug : gcc-debug
release : gcc

main : $(OBJECTS_FILES)

clean :
	rm -f *.o
