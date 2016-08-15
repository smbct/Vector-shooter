EXEC=shooter

CC=g++
CXX=g++
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS=-I include

OPTIONS=-std=c++11 -W -Wall -Wextra -pedantic -Wno-sign-compare -Wno-unused-parameter

.PHONY = clean

OBJECTS_FILES = main.o src/TextureManager.o src/Game.o src/Entity.o src/EntityManager.o \
				src/Player.o src/Enemy.o src/Bullet.o src/ScoreManager.o \
				src/BlackHole.o src/EnemySpawner.o 

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
	find . -name "*.o" -type f -delete
