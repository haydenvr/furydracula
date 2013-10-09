CC=gcc
CFLAGS=-Wall -Werror -g

all: 
	$(CC) $(CFLAGS) -o testHunterView HunterView.c testHunterView.c

clean:
	rm -rf testHunterView

