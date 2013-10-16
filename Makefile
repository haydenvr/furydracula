CC=gcc
CFLAGS=-Wall -Werror -g

test1: 
	$(CC) $(CFLAGS) -o testHunterView HunterView.c testHunterView.c Graph.c

test3: 
	$(CC) $(CFLAGS) -o testHunterView3 HunterView.c testHunterView3.c Graph.c

test4:
	$(CC) $(CFLAGS) -o testHunterView4 HunterView.c testHunterView4.c Graph.c

testAi:
	$(CC) $(CFLAGS) -o testHunter HunterView.c testHunter.c hunter.c Graph.c

graphT:
	$(CC) $(CFLAGS) -o testGraph HunterView.c testHunterView2.c Graph.c

clean:
	rm -rf testHunterView testHunterView2 testHunterView3 testGraph testHunter

