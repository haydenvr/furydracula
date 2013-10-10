CC=gcc
CFLAGS=-Wall -Werror -g

test1: 
	$(CC) $(CFLAGS) -o testHunterView HunterView.c testHunterView.c graph/Graph.c

graphT:
	$(CC) $(CFLAGS) -o testGraph HunterView.c testHunterView2.c graph/Graph.c

clean:
	rm -rf testHunterView testHunterView2 testHunterView3 testGraph

