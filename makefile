CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -g
LDFLAGS = -lm
OBJECTS = main.o card.o
PROGRAM = blackjack.exe

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c

main.o: main.c card.h
	$(CC) $(CFLAGS) -c main.c

clean:
	del -vf *.o $(PROGRAM)
