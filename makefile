CC = gcc
CFLAGS = -Wall

all: zad1 zad2 zad3 zad4

zad1: zad1.c
	$(CC) $(CFLAGS) -o zad1 zad1.c

zad2: zad2.c
	$(CC) $(CFLAGS) -o zad2 zad2.c

zad3: zad3.c
	$(CC) $(CFLAGS) -o zad3 zad3.c

zad4: zad4.c
	$(CC) $(CFLAGS) -o zad4 zad4.c

clean:
	rm -f zad1 zad2 zad3 zad4
