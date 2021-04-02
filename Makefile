LFLAGS=-std=c99
CC=gcc

all:
	$(CC) $(LFLAGS) -o readdir readdir.c
	$(CC) $(LFLAGS) -o getopt-example getopt-example.c
