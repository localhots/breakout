CC=clang++

all: build run

build:
	$(CC) -lSDL2 main.cpp -o breakout

run:
	./breakout
