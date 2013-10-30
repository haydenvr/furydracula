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
    /*
    {
        playerMessage messages2[] = {
	    "camping",
	    "",
	    "",
	    "",
	    "+++Mr. Jelly! Mr. Jelly!+++",
	    "I'm camping MAN!!!",
	    "",
	    "",
	    "pn\u001a\thF\u001a\t\u0003",
	    "+++Mr. Jelly! Mr. Jelly!+++",
	    "I'm camping MAN!!!",
	    "VR",
	    "VR",
	    "VR",
	    "+++Oneoneoneoneoneoneone+++",
	    "I'm camping MAN!!!"
	  };
        printf("Testing player 2 fail case round 5. Tried moving from Liverpool -> London\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DGA.V.. GCD.... SBE.... HST.... MMA.... DBCT... GCD.... SKL.... HMU.... MMA.... DHIT... GCD.... SGAV... HVI.... MMA.... DD1T... GCD.... SGA.... HBD.... MMA.... DCNT... GCD.... SGA.... HKL.... MMA.... DC?T... GCD.... SGA.... HGA.... MMA.... DBS.... GCD.... SGA.... HGA.... MMA.... DS?..M. GCD.... SGA.... HGA.... MMA.... DSAT.M. GCD.... SGA.... HGA.... MMA.... DD2..M. GCD.... SGA.... HCNT... MMA.... DTS.... GCD.... SGA.... HCN.... MMA.... DCGT.M. GCD.... SGA.... HBS.... MMA.... DHIT... GCD.... SGA.... HBS.... MMA.... DMS.... GCD.... SGA.... HIO.... MMA.... DS?..M. GCD.... SGA.... HIO.... MMA.... DEC.... GCD.... SGA.... HTS.... MMA.... DLOT... GCD.... SGA.... HTS.... MMA.... DD1T.M. GCD.... SGA.... HTS.... MMA.... DHIT.M. GCD.... SGA.... HMS.... MMA.... DSWT... GCD.... SGA.... HMS.... MMA.... DS?.... GCD.... SGA.... HAO.... MMA.... DLVT... GCD.... SGA.... HAO.... MMA.... DC?T.M. GCD.... SGA.... HAO.... MMA.... DD5T.M. GCD.... SGA.... HAO.... MMA.... DPLT.M. GCD.... SGA.... HIS.... MMA.... DS?..M. GCD.... SGA.... HIS.... MMA.... DC?.V.. GCD.... SGA.... HLVT... MMA.... DC?T... GCD.... SGA.... HLV.... MMA.... DC?T.M. GCD.... SGA.... HLV.... MMA.... DD1T.M. GCD.... SGA....",messages2);
        decideMove(gameState);
        printf("latest play is %s\n",latestPlay);
        disposeHunterView(gameState);
        printf("Congrats, test should pass\n");
    } */
    {
        playerMessage messages[13] = {""};
        printf("Testing player 2 fail case round 5. Tried moving from Madrid -> Bordeaux\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DGA.V.. GCD.... SBE.... HST.... MMA.... DC?T... GCD.... SKL.... HMU....", messages);
        decideMove(gameState);
        printf("latest play is %s\n",latestPlay);
        disposeHunterView(gameState);
        printf("Congrats, test should pass\n");
    }
    {
        playerMessage messages[13] = {""};
        printf("Testing player 2 fail case round 5. Player One is making segFaults! player at Vienna\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DGA.V.. GCD.... SBE.... HST.... MMA.... DC?T... GCD.... SKL.... HMU.... MMA.... DC?T... GCD.... SGAV... HVI.... MMA.... DD1T... GCD.... SGA....",messages);
        decideMove(gameState);
        printf("latest play is %s\n",latestPlay);
        disposeHunterView(gameState);
        printf("Congrats, test should pass\n");
    }
    {
        playerMessage messages[31] = {""};
        printf("Testing player 1 fail case from game 303 round 6\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DCG.V.. GCD.... SBE.... HST.... MMA.... DS?.... GCD.... SSA.... HGE.... MAL.... DS?.... GCD.... SIO.... HMR.... MMS.... DC?T... GCD.... STS.... HMS.... MCGV... DC?T... GCD.... SCG.... HCG.... MCG.... DC?T... GCD....",messages);
        decideMove(gameState);
        printf("latest play is %s\n",latestPlay);
        disposeHunterView(gameState);
        printf("Congrats, this segfaulted in the game\n");
    }
    {
        playerMessage messages[32] = {""};
        printf("Testing player 2 fail case from game 303 round 6\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DCG.V.. GCD.... SBE.... HST.... MMA.... DS?.... GCD.... SSA.... HGE.... MAL.... DS?.... GCD.... SIO.... HMR.... MMS.... DC?T... GCD.... STS.... HMS.... MCGV... DC?T... GCD.... SCG.... HCG.... MCG.... DC?T... GCD.... SCG....",messages);
        decideMove(gameState);
        printf("latest play is %s\n",latestPlay);
        disposeHunterView(gameState);
        printf("Congrats, this segfaulted in the game\n");
    }
	{
		playerMessage messages[26] = {""};
    	printf("Testing player 1 fail case from game 39 round 9. player making illegal move from Constanta (but was (TD) so health would be -3)\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DBS.... GCD.... SBE.... HST.... MMA.... DCNT... GCD.... SCNTD.. HMU.... MAL.... DC?T... GCD.... SCN.... HZA.... MMS.... DD2T... GCD.... SCNTD.. HSZ.... MTS.... DC?T... GCD....",messages);
		decideMove(gameState);
        printf("HIS LATEST PLAY IS %s\n",latestPlay);
        disposeHunterView(gameState);
	}
	{
		playerMessage messages[152] = {""};
    	printf("Testing player 2 fail case from game 199. player returning \"\" for move. Player in Tyrrhehian Sea.\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DAL.V.. GCD.... SBE.... HST.... MMA.... DC?T... GCD.... SSA.... HGE.... MALV... DSNT... GCD.... SIO.... HMR.... MAL.... DS?.... GCD.... STS.... HMS.... MAL.... DNAT... GCD.... SMS.... HAL.... MAL.... DHIT... GCD.... SAL.... HAL.... MAL.... DCFT... GCD.... SAL.... HAL.... MAL.... DTOT.M. GCD.... SMA.... HSNT... MSN.... DD1T... GCD.... SMA.... HSN.... MSN.... DBAT... GCD.... SBO.... HBB.... MBB.... DSRT.M. GCD.... SBO.... HBB.... MBB.... DHIT.M. GCD.... SCFT... HBO.... MBO.... DMAT... GCD.... SCF.... HBO.... MBO.... DC?.VM. GCD.... SCF.... HBO.... MBO.... DCAT.M. GCD.... STO.... HSRTT.. MSR.... DD1T.M. GCD.... SSR.... HSR.... MSR.... DAO.... GCD.... SSR.... HSR.... MSR.... DS?.... GCD.... SMAT... HMA.... MMA.... DCGT... GCD.... SMA.... HMA.... MMA.... DHIT.V. GCD.... SCATT.. HCA.... MCA.... DTS.... GCD.... SCA.... HCA.... MCA.... DROT... GCD.... SAO.... HAO.... MAO.... DD1T... GCD.... SAO.... HAO.... MAO.... DBIT... GCD.... SMS.... HMS.... MMS.... DNPT.M. GCD.... SMS.... HMS.... MMS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DTP.V.. GCDVD.. STS.... HTS.... MTS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DD1T.M. GCD.... STS....",messages);
		decideMove(gameState);
        printf("HIS LATEST PLAY IS (%s)\n",latestPlay);
        disposeHunterView(gameState);
	}
	{
		playerMessage messages[149] = {""};
    	printf("Testing player 3 fail case from game 199. player seg faulting. Player in Tyrrhehian Sea.\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DAL.V.. GCD.... SBE.... HST.... MMA.... DC?T... GCD.... SSA.... HGE.... MALV... DSNT... GCD.... SIO.... HMR.... MAL.... DS?.... GCD.... STS.... HMS.... MAL.... DNAT... GCD.... SMS.... HAL.... MAL.... DHIT... GCD.... SAL.... HAL.... MAL.... DCFT... GCD.... SAL.... HAL.... MAL.... DTOT.M. GCD.... SMA.... HSNT... MSN.... DD1T... GCD.... SMA.... HSN.... MSN.... DBAT... GCD.... SBO.... HBB.... MBB.... DSRT.M. GCD.... SBO.... HBB.... MBB.... DHIT.M. GCD.... SCFT... HBO.... MBO.... DMAT... GCD.... SCF.... HBO.... MBO.... DC?.VM. GCD.... SCF.... HBO.... MBO.... DCAT.M. GCD.... STO.... HSRTT.. MSR.... DD1T.M. GCD.... SSR.... HSR.... MSR.... DAO.... GCD.... SSR.... HSR.... MSR.... DS?.... GCD.... SMAT... HMA.... MMA.... DCGT... GCD.... SMA.... HMA.... MMA.... DHIT.V. GCD.... SCATT.. HCA.... MCA.... DTS.... GCD.... SCA.... HCA.... MCA.... DROT... GCD.... SAO.... HAO.... MAO.... DD1T... GCD.... SAO.... HAO.... MAO.... DBIT... GCD.... SMS.... HMS.... MMS.... DC?T.M. GCD.... SMS.... HMS.... MMS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DTP.V.. GCDVD.. STS.... HTS.... MTS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DC?T.M. GCD.... STS.... HTS....",messages);
		decideMove(gameState);
        printf("HIS LATEST PLAY IS (%s)\n",latestPlay);
        disposeHunterView(gameState);
	}
	{
		playerMessage messages[140] = {""};
    	printf("Testing player 1 fail case from game 199. player seg faulting. Player in Tyrrhehian Sea.\n");
        gameState = newHunterView("GCD.... SBE.... HST.... MMA.... DAL.V.. GCD.... SBE.... HST.... MMA.... DC?T... GCD.... SSA.... HGE.... MALV... DSNT... GCD.... SIO.... HMR.... MAL.... DS?.... GCD.... STS.... HMS.... MAL.... DNAT... GCD.... SMS.... HAL.... MAL.... DHIT... GCD.... SAL.... HAL.... MAL.... DCFT... GCD.... SAL.... HAL.... MAL.... DTOT.M. GCD.... SMA.... HSNT... MSN.... DD1T... GCD.... SMA.... HSN.... MSN.... DBAT... GCD.... SBO.... HBB.... MBB.... DSRT.M. GCD.... SBO.... HBB.... MBB.... DHIT.M. GCD.... SCFT... HBO.... MBO.... DMAT... GCD.... SCF.... HBO.... MBO.... DC?.VM. GCD.... SCF.... HBO.... MBO.... DCAT.M. GCD.... STO.... HSRTT.. MSR.... DD1T.M. GCD.... SSR.... HSR.... MSR.... DAO.... GCD.... SSR.... HSR.... MSR.... DS?.... GCD.... SMAT... HMA.... MMA.... DCGT... GCD.... SMA.... HMA.... MMA.... DHIT.V. GCD.... SCATT.. HCA.... MCA.... DTS.... GCD.... SCA.... HCA.... MCA.... DC?T... GCD.... SAO.... HAO.... MAO.... DD1T... GCD.... SAO.... HAO.... MAO.... DC?T... GCD.... SMS.... HMS.... MMS.... DC?T.M. GCD.... SMS.... HMS.... MMS.... DC?T.M. GCD.... STS.... HTS.... MTS.... DTP.V.. GCDVD..",messages);
		decideMove(gameState);
        printf("HIS LATEST PLAY IS (%s)\n",latestPlay);
        disposeHunterView(gameState);
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
    printf("Passed\nNow testing same path but without rail (ie round rem 4 equal to 0 )");
    printf("Passed\nNow testing same path but without rail");
    a = findShortestPath(STRASBOURG, CASTLE_DRACULA, path, ANY, 0);
    int correct2[6] = {51,38,58,10,28,13};
    for (i = 0; i < a; i++) {
        assert(path[i] == correct2[i]);
    }
    printf("\nTest Passed\nNow to test the results of connected locs Klaus (expecting CD to be there)\n");  
    Graph g = newGraph();
    LocationID *b = connectedLocations(&a, KLAUSENBURG, 0, 0, ANY, g);
    for (i=0; i<a; i++) {
        printf("[%d]",b[i]);
    }
    free(b);
    destroyGraph(g);
    printf("\nDone\n");
}

