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
