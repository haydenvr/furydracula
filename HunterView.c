#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "game.h"
#include "HunterView.h"
#include "graph/Graph.h"

typedef struct player *Player;
     
struct hunterView {
	int score;
    Round round;
    PlayerID currentPlayer;
    Player players[NUM_PLAYERS];
    char *pastPlays;
    playerMessage messages[MESSAGE_SIZE];
};

struct player {
    int health;
    LocationID location;
};

// newHunterView creates a new hunter view to summarise the current state of
// the game.
//
// pastPlays is a string of all the plays made in the game so far by all
// players (including Dracula) from earliest to most recent.
//
//
// messages is an array containing a playerMessage for each play in the game
// so far. It will have exactly the same number of elements as there are plays
// in pastPlays. The message from the first play will be at index 0, and so on.
// The contents of each playerMessage will be exactly as provided by the player.
//
// The "playerMessage" type is defined in game.h.
// You are free to ignore messages if you wish.
HunterView newHunterView( char *pastPlays, playerMessage messages[] ) {
    HunterView hunterView = malloc( sizeof( struct hunterView ) );
	//printf("the length of string is %lu\n",sizeof(*pastPlays));
	int i = 0;
	int player;
	char *locations[] = {
	"AL", "AM", "AT", "BA", "BI", "BE", "BR", "BO", "BU", "BC", 
	"BD", "CA", "CG", "CD", "CF", "CO", "CN", "DU", "ED", "FL",
	"FR", "GA", "GW", "GE", "GO", "GR", "HA", "JM", "KL", "LE",
	"LI", "LS", "LV", "LO", "MA", "MN", "MR", "MI", "MU", "NA",
	"NP", "NU", "PA", "PL", "PR", "RO", "SA", "SN", "SR", "SJ",
	"SO", "ST", "SW", "SZ", "TO", "VA", "VR", "VE", "VI", "ZA",
	"ZU",
	"NS", "EC", "IS", "AO", "BB", "MS", "TS", "IO", "AS", "BS",	
	"C?", "S?", "HI", "D1", "D2", "D3", "D4", "D5", "TP"
	};
	for (i = 0; i < NUM_PLAYERS; i++) {
        hunterView->players[i] = malloc (sizeof (struct player));
		hunterView->players[i]->health = 9;
		if (i == 4) hunterView->players[i]->health = 40;
        hunterView->players[i]->location = -1;
    }
	i = 0;
	while (pastPlays[i] != '\0') {
			//this character should represent the player name
			if (pastPlays[i] == 'G') player = PLAYER_LORD_GODALMING;
			else if (pastPlays[i] == 'S') player = PLAYER_DR_SEWARD;
			else if (pastPlays[i] == 'H') player = PLAYER_VAN_HELSING;
			else if (pastPlays[i] == 'M') player = PLAYER_MINA_HARKER;
			else if (pastPlays[i] == 'D') player = PLAYER_DRACULA;
			else {
				perror("Something is wrong with pastPlays\n");
				abort();
			}
			
			i++;
			int z = 0;
			
			char a[] = {pastPlays[i], pastPlays[i+1]};
			
			while (z < NUM_LOCATIONS && (locations[z][0] != a[0] || locations[z][1] != a[1])) z++;
			hunterView->players[player]->location = z;
			
			i += 2;
			i+= 4; //test purposes
			if (pastPlays[i] == ' ') i++;
			printf("%d\n",player);
		//}
		//round++;		
		//i++;
	}
	i = (i+1)/8;
	printf("the size is %d",i);
    hunterView->round = i/5;
    hunterView->currentPlayer = 0;
    hunterView->pastPlays = pastPlays;
	hunterView->score = 366;
    int j;
	int amt_mess = (int) sizeof(messages)/sizeof(playerMessage);
	for (i = 0; i < amt_mess; i++) {
		for (j = 0; j < MESSAGE_SIZE-1; j++){
			if (messages[i][j] == '\0') break;
			hunterView->messages[i][j] = messages[i][j];
			
		}
	}
    return hunterView;
}
     
     
// this function frees all memory previously allocated for the HunterView
// toBeDeleted. toBeDeleted should not be accessed after the call.
void disposeHunterView( HunterView toBeDeleted ) {
    free( toBeDeleted );
}

//Functions to return simple information about the current state of the game

//Get the current round
Round getRound (HunterView currentView) {
	return currentView->round;
}

//Get the id of current player - ie whose turn is it?
// Only returns a 'playerID' which is one of:
//   LORD_GODALMING (0): Lord Godalming's turn
//   DR_SEWARD      (1): Dr. Seward's turn
//   VAN_HELSING    (2): Van Helsing's turn
//   MINA_HARKER    (3): Mina Harker's turn
//   DRACULA        (4): Dracula's turn
PlayerID getCurrentPlayer (HunterView currentView) {
	assert(currentView->currentPlayer >= 0 && currentView->currentPlayer <= 4);
	return currentView->currentPlayer;
}

//Get the current score
// Returns a positive integer [0...366]
int getScore(HunterView currentView) {
	assert(currentView->score >= 0);
	return currentView->score;
}

//Get the current health points for a given player
// 'player' specifies which players's life/blood points to return
//    and must be a value in the interval [0...4] (see 'player' type)
int getHealth(HunterView currentView, PlayerID player) {
	assert(player >= 0 && player <= 4);
	return currentView->players[player]->health;
}

// Get the current location id of a given player
// May be UNKNOWN_LOCATION if the player has not had a turn yet
// (ie at the beginning of the game when the round is 0)
// otherwise for a hunter it should be an integer in the interval [0..70] 
// The given roundNumber is >= 0 and <= the current round number
// 'whichHunter' specifies which hunter's location to return
//    and must be a value in the interval [0...3] (see 'player' type)
// Or for dracula it should 
// gets the location of Dracula at the start of a particular round
// Returns an integer:
//   in the interval [0...70] if Dracula was known to be in a city or sea
//   CITY_UNKNOWN     if Dracula was in an unknown city
//   SEA_UNKNOWN      if Dracula was in an unknown sea
//   HIDE             if Dracula was known to have made a hide move
//   DOUBLE_BACK_N    where N is [0...5], if Dracula was known to have 
//                    made a double back move N positions back in the trail
//                    e.g. DOUBLE_BACK_1 is the last place place he visited
//   TELEPORT         if Dracula apparated back to Castle Dracula
//   LOCATION_UNKNOWN if the round number is 0
LocationID getLocation(HunterView currentView, PlayerID player) {
	return currentView->players[player]->location;
}

//Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns for the given player
// For dracula this may include integers:
//   in the interval [0...70] if Dracula was known to be in a city or sea
//   CITY_UNKNOWN     if Dracula was in an unknown city
//   SEA_UNKNOWN      if Dracula was in an unknown sea

//   HIDE             if Dracula was known to have made a hide move
//   DOUBLE_BACK_N    where N is [0...5], if Dracula was known to have
//                    made a double back move N positions back in the trail
//                    e.g. DOUBLE_BACK_1 is the last place place he visited
//   TELEPORT         if Dracula apparated back to Castle Dracula


// For any player if the move does not exist yet (i.e, the start of the game),
// the value should be UNKNOWN_LOCATION (-1)
// For example after 2 turns the array may have the contents
// {29, 182, -1, -1, -1, -1} 
// This would mean in the first move the player started on location 182 
// then moved to the current location of 29
void getHistory (HunterView currentView, PlayerID player,LocationID trail[TRAIL_SIZE]) {

}

//Functions that query the map to find information about connectivity

//This function returns an array of LocationID that represent all locations that are connected 
//to the given LocationID. 
//road, rail and sea are connections should only be considered if the road, rail, sea parameters 
//are TRUE.
//The size of the array should be stored in the variable pointed to by numLocations
//The array can be in any order but must contain unique entries
//Your function must take into account the round and player id for rail travel
//Your function must take into account that dracula can't move to the hospital or travel by rail
//but need not take into account draculas trail
//The destination 'from' should be included.
LocationID * connectedLocations(HunterView currentView, int * numLocations, LocationID from, 
                              PlayerID player, Round round, int road, int rail, int sea) {
	//this should come from graph file. 
	return NULL;
}

