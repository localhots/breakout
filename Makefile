CC=clang++

all: build run

build:
	$(CC) -lSDL2 src/scene.cpp src/breakout.cpp -o breakout

run:
	./breakout
