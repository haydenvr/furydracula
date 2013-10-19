all: HunterView.h hunter.h
	gcc -g -o testHunter HunterView.c testHunter.c hunter.c Graph.c
clean:
	rm -rf testHunter
