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

}

PlayerID getCurrentPlayer (HunterView currentView) {

}

int getScore(HunterView currentView) {

}

int getHealth(HunterView currentView, PlayerID) {

}

LocationID getLocation(HunterView currentView, PlayerID) {

}

void getHistory (HunterView currentView, PlayerID player,LocationID trail[TRAIL_SIZE]) {

}

LocationID * connectedLocations(HunterView currentView, int * numLocations, LocationID from, 
                              PlayerID player, Round round, int road, int rail, int sea) {



