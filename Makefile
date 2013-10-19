CC=gcc
CFLAGS=-Wall -Werror -g

make:
	$(CC) $(CFLAGS) -c Graph.c HunterView.c Graph.c hunter.c -ljiansson

clean:
	rm -rf testHunterView testHunterView2 testHunterView3 testGraph testHunter

