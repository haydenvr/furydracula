CC=gcc
CFLAGS=-Wall -Werror -g

test1: 
	$(CC) $(CFLAGS) -o testHunterView HunterView.c testHunterView.c graph/Graph.c

test2: 
	$(CC) $(CFLAGS) -o testHunterView2 HunterView.c testHunterView2.c graph/Graph.c

test3:
	$(CC) $(CFLAGS) -o testHunterView3 HunterView.c testHunterView3.c graph/Graph.c

graphT:
	$(CC) $(CFLAGS) -o testGraph HunterView.c testHunterView2.c graph/Graph.c

clean:
	rm -rf testHunterView testHunterView2 testHunterView3 testGraph

