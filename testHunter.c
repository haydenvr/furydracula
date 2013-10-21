/**
 * Compiles with:
 *  gcc -Wall -Werror -o testHunter game.c hunter.c HunterView.c 
 * 
 * (And any additional files you wrote for HunterView implementation)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "game.h"
#include "cities.h"
#include "HunterView.h"
#include "hunter.h"
#include "Graph.h"

//includes '\0'
#define MOVE_SIZE 3

static char latestPlay[MOVE_SIZE] = "";

void testInitialMoves(void);
void testMovesRound1(void);
void testAll(void);
void testGraph(void);

int main( int argc, char *argv[] ) {
    testAll();
    return EXIT_SUCCESS;
}

void testAll(void){
    testInitialMoves();
    testMovesRound1();
    testGraph();
}

int moveIn(char * locs[], int size){
    int i;
    for(i=0; i< size; i++){
        if(strcmp(latestPlay,locs[i]) == 0) return 1;
    }
    return 0;
}

void testMovesRound1(void){
      HunterView gameState;
     
    {
       playerMessage messages[7] = {""};
       printf("Test: Round 1 hunter 2 move. Testing his connected locs.\n");
       printf("creating hunterview.\n");
       gameState = newHunterView("GGW.... SGA.... HAT.... MMA.... DBO.V.. GGW.... SKL....",messages);
       printf("deciding move.\n");
       decideMove( gameState );
       printf("disposing.\n");
       disposeHunterView( gameState );
       printf("Test passed\n");
   }
/*
	{
       playerMessage messages[7] = {""};
       printf("Test: Round 1 hunter 3 moves from MA\n");
       gameState = newHunterView("GGW.... SGA.... HAT.... MMA.... DBO.V.. GGW.... SKL.... HPR....",messages);
       decideMove( gameState );
       disposeHunterView( gameState );
       char * possibleLocations[7] = {"LS","CA","GR","SR","AL","SN","MA"};
       assert(moveIn(possibleLocations,7));
       printf("Test passed\n");
   }
*/

}

void testInitialMoves(void){
   //HunterView gameState;
/*
   {
       playerMessage messages[] = {};
       printf("Test 1: Round 0 hunter 0 in GW\n");   
       gameState = newHunterView("",messages);
       decideMove( gameState );
       disposeHunterView( gameState );   
       assert(strcmp(latestPlay,"GW") == 0);
       printf("Test passed\n");
   }   

   {
       playerMessage messages[] = {""};                                                        
       printf("Test 2: Round 0 hunter 1 in GA\n");                 
       gameState = newHunterView("GGW....",messages);
       decideMove( gameState );
       disposeHunterView( gameState );
       assert(strcmp(latestPlay,"GA") == 0);
       printf("Test passed\n");
   }

    {
       playerMessage messages[2] = {""};
       printf("Test 3: Round 0 hunter 2 in AT\n");
       gameState = newHunterView("GGW.... SGA....",messages);
       decideMove( gameState );
       disposeHunterView( gameState );
       assert(strcmp(latestPlay,"AT") == 0);
       printf("Test passed\n");
   }
   
    {
       playerMessage messages[3] = {""};
       printf("Test 4: Round 0 hunter 3 in MA\n");
       gameState = newHunterView("GGW.... SGA.... HAT....",messages);
       decideMove( gameState );
       disposeHunterView( gameState );
       assert(strcmp(latestPlay,"MA") == 0);
       printf("Test passed\n");
   }*/
}

// Saves characters from play (and appends a terminator)
// and saves characters from message (and appends a terminator)
void registerBestPlay ( char *play, playerMessage message ) {
   strncpy( latestPlay, play, MOVE_SIZE-1 );
   latestPlay[MOVE_SIZE-1] = '\0';
}

void testGraph(void) {
    printf("Testing graph 1...\n");
    Location path[NUM_MAP_LOCATIONS];
    int a = findShortestPath(NANTES, MARSEILLES, path, ANY,0);
    assert(a == 3);
    assert(path[0] == NANTES);
    assert(path[1] == CLERMONT_FERRAND);
    assert(path[2] == MARSEILLES);
    printf("Test passed!\n");   
    printf("Testing graph 2...\n");
    a = findShortestPath(NANTES, MARSEILLES, path, ANY,0);
    assert(a == 3);
    assert(path[0] == NANTES);
    assert(path[1] == CLERMONT_FERRAND);
    assert(path[2] == MARSEILLES);
    printf("Test passed!\n");
	printf("Testing graph by rail...\n");
    a = findShortestPath(MADRID, BARCELONA, path, ANY,2); 
	assert(a == 2);
	assert(path[0] == MADRID);
    assert(path[1] == BARCELONA);  
	printf("Passed by rail test\n");
	a = findShortestPath(MARSEILLES, COLOGNE, path, ANY,3); 
	assert(a == 2);
	assert(path[0] == MARSEILLES);
    assert(path[1] == COLOGNE); 
	printf("Passed second rail test\n");
	a = findShortestPath(MARSEILLES, AMSTERDAM, path, ANY,3); 
	assert(a == 3);
	assert(path[0] == MARSEILLES);
    assert(path[1] == COLOGNE); 
	assert(path[2] == AMSTERDAM); 
	printf("Passed final rail test\n");
}

