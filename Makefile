CC=gcc
CFLAGS=-Wall -Werror -g

test1: 
	$(CC) $(CFLAGS) -o testHunterView HunterView.c testHunterView.c

test2: 
	$(CC) $(CFLAGS) -o testHunterView2 HunterView.c testHunterView2.c

graphT:
	$(CC) $(CFLAGS) -o testGraph HunterView.c testHunterView2.c graph/Graph.c

clean:
	rm -rf testHunterView testHunterView2 testGraph

