#include "game.h"
#include "HunterView.h"
#include "hunter.h"
#include "Graph.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NUM_HUNTERS (NUM_PLAYERS - 1)

void decideMove (HunterView gameState) {
	Graph g = newGraph();
    char *locations[] = {
        "AL", "AM", "AT", "BA", "BI", "BE", "BR", "BO", "BU", "BC", 
        "BD", "CA", "CG", "CD", "CF", "CO", "CN", "DU", "ED", "FL",
        "FR", "GA", "GW", "GE", "GO", "GR", "HA", "JM", "KL", "LE",
        "LI", "LS", "LV", "LO", "MA", "MN", "MR", "MI", "MU", "NA",
        "NP", "NU", "PA", "PL", "PR", "RO", "SA", "SN", "SR", "SJ",
        "SO", "ST", "SW", "SZ", "TO", "VA", "VR", "VE", "VI", "ZA",
        "ZU", "NS", "EC", "IS", "AO", "BB", "MS", "TS", "IO", "AS", 
        "BS", "C?", "S?", "HI", "D1", "D2", "D3", "D4", "D5", "TP"
	};
	int round = getRound(gameState);
	in
	PlayerID id = getCurrentPlayer(gameState);
    LocationID move = getLocation(gameState, id);
	char * msg = "";
    printf("hi there the round is %d\n",round);	
	//set initial locations
	if (round - id == 0) {
	    if (id == PLAYER_LORD_GODALMING) {move = CASTLE_DRACULA; msg = "camping";}
	    else if (id == PLAYER_DR_SEWARD)  move = BELGRADE;
	    else if (id == PLAYER_VAN_HELSING) move = STRASBOURG;
	    else if (id == PLAYER_MINA_HARKER) move = MADRID;
	    registerBestPlay(locations[move], msg);
	    return;
    }
    
    if (id == PLAYER_LORD_GODALMING) { registerBestPlay("CD","I'm camping MAN!!!"); return; }
	srand (time(NULL));
	int path[NUM_MAP_LOCATIONS];
    int amtLocs = 0;
    LocationID * adj = connectedLocations(&amtLocs, getLocation(gameState, id), id, round, ANY, g);
    LocationID target = UNKNOWN_LOCATION;
    int camper = 1, i;
    
    // check for campers
    // if the current player is camping, then the player
    // will stay camping and ai will return
    /* not necessary as LG is always camping
    for (i = 0; i < NUM_HUNTERS; i++) {
        if (getLocation(gameState, i) == CASTLE_DRACULA) {
            camper = 1;
            if (id == i) {
	            registerBestPlay("CD", "Staying camping");
                return; 
            }
        }
    } */   

    if (!camper) {
        //if no camper and hunter is shortest dist to castle dracula, move towards castle dracula
        int hunterDist[NUM_HUNTERS] = {UNKNOWN_LOCATION,UNKNOWN_LOCATION,UNKNOWN_LOCATION,UNKNOWN_LOCATION};
        int closestHunter = PLAYER_LORD_GODALMING;
        LocationID adj;
        for (i = PLAYER_LORD_GODALMING; i < NUM_HUNTERS; i++) {
            hunterDist[i] = findShortestPath(getLocation(gameState, i), CASTLE_DRACULA, path, ANY, round);
            if (hunterDist[i] == -1) hunterDist[i] = 1000; //-1 is when there is no path, so don't want him to be shortest

            if ((hunterDist[closestHunter] > hunterDist[i]) || (hunterDist[closestHunter] == UNKNOWN_LOCATION)) {
                 adj = path[1];
                 closestHunter = i;
            }
        }
        if (closestHunter == id) move = adj;
    } else {
        //Note: Dracula cannot visit any location currently in his trail - hunters should not visit target itself!
        
        //set target to message history
        if (getLatestMessageLoc(gameState) != UNKNOWN_LOCATION) target = getLatestMessageLoc(gameState);
        // what is the point of this line?
        
        LocationID draculaLoc[TRAIL_SIZE];
        getHistory (gameState, PLAYER_DRACULA, draculaLoc);
        for (i = TRAIL_SIZE - 1; i >= 0 ; i--) { //locations newer in trail will override older ones
            //if we have any useful info on his location...
            if (draculaLoc[i] != CITY_UNKNOWN && draculaLoc[i] != SEA_UNKNOWN && draculaLoc[i] != HIDE) {
                if (draculaLoc[i] >= DOUBLE_BACK_1 && draculaLoc[i] <= DOUBLE_BACK_5) { //double back found
                    int dbVal = i - (draculaLoc[i] - DOUBLE_BACK_1 + 1);
                    if (dbVal >= 0) { //double back location still in trail; segfault prevention
                        LocationID dbLoc = draculaLoc[dbVal];
                        if (dbLoc != CITY_UNKNOWN && dbLoc != SEA_UNKNOWN && dbLoc != HIDE) target = dbLoc;
                    }
                } else { //we found his location!
                    msg = locations[draculaLoc[i]];
                    target = draculaLoc[i];
                }
            }
        }

        if (target == UNKNOWN_LOCATION) target = adj[rand() % amtLocs]; //location unknown - move randomly
        else {
        	int successful = findShortestPath(getLocation(gameState, id), target, path, ANY, round);//success is any number not -1
        	if (successful != -1) move = path[1];
            printf("hi im here and move is %d and target is %d\n",move,target);
		}
        //while (adj[rand() % amtLocs] == target) move = adj[rand() % amtLocs];

    }
    /*
    if (move == CASTLE_DRACULA && camper) { //don't double up campers!
        while (adj[rand() % amtLocs] == target || adj[rand() % amtLocs] == CASTLE_DRACULA) move = adj[rand() % amtLocs];
    }*/
    destroyGraph(g);
    printf("my move is %d\n",move);
	registerBestPlay(locations[move], msg);
}

