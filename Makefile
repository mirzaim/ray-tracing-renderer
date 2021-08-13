
CC = g++
FLAGS = -Wall -std=c++17


SRCS = main.cpp
TARGET = build/main

all:
	$(CC) $(FLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f build/*