FLAGS = -g -Wall -Wextra -Werror -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OUTPUT = app
CC = clang++

all: build run

build: app

clean:
	rm *.o

app: test.o PixelSorter.o
	$(CC) $(FLAGS) -o $(OUTPUT) test.o PixelSorter.o $(LFLAGS)

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

PixelSorter.o: PixelSorter.cpp
	$(CC) $(FLAGS) -c PixelSorter.cpp

run: build
	./app
