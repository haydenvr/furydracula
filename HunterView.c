#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
#include "graph/Graph.h"
     
struct hunterView {
	int score;
    Round round;
    PlayerID currentPlayer;
    Player players[NUM_PLAYERS];
    char *pastPlays;
    playerMessage messages[];
};

struct player {
    int health;
    LocationID location;
};

typedef struct player *Player;
     

HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
    hunterView->round = 1;
    hunterView->currentPlayer = 0;
    hunterView->pastPlays = pastPlays;
    hunterView->messages = messages;
    int i;
    for (i = 0; i < NUM_PLAYERS; i++) {
        hunterView->players[i]->score = 0;
        hunterView->players[i]->health = 0;
        hunterView->players[i]->location = 0;
    }
    return hunterView;
}
     
     
// this function frees all memory previously allocated for the HunterView
// toBeDeleted. toBeDeleted should not be accessed after the call.
void disposeHunterView( HunterView toBeDeleted ) {
    int i;
    for (i = 0; i < NUM_PLAYERS; i++) free(toBeDeleted->players[i]);
    free( toBeDeleted );
}

Round getRound (HunterView currentView) {
	return currentView->round;
}

PlayerID getCurrentPlayer (HunterView currentView) {
	return currentView->currentPlayer;
}

int getScore(HunterView currentView) {
	return currentView->score;
}

int getHealth(HunterView currentView, PlayerID) {
	return currentView->players[PlayerID]->health;
}

LocationID getLocation(HunterView currentView, PlayerID) {
	return currentView->players[PlayerID]->location;
}

void getHistory (HunterView currentView, PlayerID player,LocationID trail[TRAIL_SIZE]) {

}

LocationID * connectedLocations(HunterView currentView, int * numLocations, LocationID from, 
                              PlayerID player, Round round, int road, int rail, int sea) {
	//this should come from graph file. 
}

