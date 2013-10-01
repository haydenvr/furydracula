#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include "HunterView.h"
     
struct hunterView {
    Round round;
    PlayerID currentPlayer;
    Player players[NUM_PLAYERS];
};

struct player {
    int score;
    int health;
    LocationID location;
};

typedef struct player *Player;
     

HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
    hunterView->round = 1;
    hunterView->currentPlayer = 0;
    int i;
    for (i = 0; i < NUM_PLAYERS; i++) {
        hunterView->players[i]->score = 0;
        hunterView->players[i]->health = 0;
        hunterView->players[i]->score = 0;
        hunterView->players[i]->location = 0;
    }
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



