LFLAGS=-std=c99
CC=gcc

all:
	$(CC) $(LFLAGS) -o cfind cfind.c
