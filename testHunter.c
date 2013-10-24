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
void testBlank(void);
void testGraph(void);

int main( int argc, char *argv[] ) {
    testInitialMoves();
    testBlank();
    testMovesRound1();
    testGraph();
    return EXIT_SUCCESS;
}

void testBlank(void){
    HunterView gameState;
     
    {
       playerMessage messages[1] = {""};
       printf("Test: blank game.\n");
       printf("creating hunterview.\n");
       gameState = newHunterView("",messages);
       printf("deciding move.\n");
       decideMove( gameState );
       printf("disposing.\n");
       disposeHunterView( gameState );
       printf("Test passed\n");
   }
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
       printf("Test1: Round 1 hunter 2 move. Testing his connected locs.\n");
       printf("creating hunterview.\n");
       gameState = newHunterView("GGW.... SGA.... HAT.... MMA.... DBO.V.. GGW.... SKL....",messages);
       printf("deciding move.\n");
       decideMove( gameState );
       printf("disposing.\n");
       disposeHunterView( gameState );
       printf("Test passed\n");

       printf("Test2: Round 1 hunter 2 move. Testing his connected locs.\n");
       printf("creating hunterview.\n");
       gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DC?.V.. GKL.... SKL.... HST....",messages);
       printf("deciding move.\n");
       decideMove( gameState );
       printf("disposing.\n");
       disposeHunterView( gameState );
       printf("Test passed\n");
   }
   {
       playerMessage messages[7] = {""};
       printf("Testing fail round 2, hunter 2 trying to move illegally to CD\n");
       gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DKL.V.. GKLVD.. SKLD...",messages);
       decideMove(gameState);
       disposeHunterView(gameState);
       printf("Test passed!\n");
       printf("latest play is %s\n",latestPlay);
    }
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
    printf("Testing fail cases\n");
    printf("Testing Strassburg to CD\n");
    a = findShortestPath(STRASBOURG, CASTLE_DRACULA, path, ANY, 3);
    int i = 0;
    int correct[5] = {51,6,10,21,13};
    for (i = 0; i < a; i++) {
        assert(path[i] == correct[i]);
    }
    printf("Passed\nNow testing same path but without rail (ie round%4==0)");
    a = findShortestPath(STRASBOURG, CASTLE_DRACULA, path, ANY, 0);
    //int correct[5] = {51,6,10,21,13};
    for (i = 0; i < a; i++) {
        printf("[%d]->",path[i]);// == correct[i]);
    }
    printf("\nDone\n");  

}

