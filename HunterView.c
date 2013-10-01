#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
     
struct hunterView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int hello;
};
     

HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
    hunterView->hello = 42;
    return hunterView;
}
     
     
// this function frees all memory previously allocated for the HunterView
// toBeDeleted. toBeDeleted should not be accessed after the call.
void disposeHunterView( HunterView toBeDeleted ) {
    //COMPLETE THIS IMPLEMENTATION
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
	return currentView->health[PlayerID];
}

LocationID getLocation(HunterView currentView, PlayerID) {
	return currentView->location[PlayerID];
}

void getHistory (HunterView currentView, PlayerID player,LocationID trail[TRAIL_SIZE]) {

}

LocationID * connectedLocations(HunterView currentView, int * numLocations, LocationID from, 
                              PlayerID player, Round round, int road, int rail, int sea) {
	//this should come from graph file. 
}

