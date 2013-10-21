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
	PlayerID id = getCurrentPlayer(gameState);
    LocationID move = getLocation(gameState, id);
	srand (time(NULL));
	int path[NUM_MAP_LOCATIONS];
	char * msg = "";
	
	//set initial locations
	if (round == 0) {
	    if (id == PLAYER_LORD_GODALMING) {move = CASTLE_DRACULA; msg = "camping";}
	    else if (id == PLAYER_DR_SEWARD)  move = BELGRADE;
	    else if (id == PLAYER_VAN_HELSING) move = STRASBOURG;
	    else if (id == PLAYER_MINA_HARKER) move = MADRID;
    }
    int camper = 0, i;
    
    //check for campers OTHER THAN CURRENT
    for (i = 0; i < NUM_HUNTERS; i++) if (i != id && getLocation(gameState, i) == CASTLE_DRACULA) camper = 1;     
    if (!camper) {
        //if no camper and hunter is shortest dist to castle dracula, move towards castle dracula
        int hunterDist[NUM_HUNTERS] = {UNKNOWN_LOCATION,UNKNOWN_LOCATION,UNKNOWN_LOCATION,UNKNOWN_LOCATION};
        int closestHunter = PLAYER_LORD_GODALMING;
        LocationID adj;
        for (i = PLAYER_LORD_GODALMING; i < NUM_HUNTERS; i++) {
            hunterDist[i] = findShortestPath(getLocation(gameState, i), CASTLE_DRACULA, path, ANY, round);
            if ((hunterDist[closestHunter] > hunterDist[i]) || (hunterDist[closestHunter] == UNKNOWN_LOCATION)) adj = path[1];
        }
        move = adj;
    } else {
        LocationID target = UNKNOWN_LOCATION;
        int j;
        //set target to message history
        if (getLatestMessageLoc(gameState) != UNKNOWN_LOCATION) target = getLatestMessageLoc(gameState);
        
        for (i = TRAIL_SIZE - 1; i >= 0 ; i--) { //locations newer in trail will override older ones
            LocationID draculaLoc[TRAIL_SIZE];
            getHistory (gameState, PLAYER_DRACULA, draculaLoc);
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
        if (target != UNKNOWN_LOCATION) target = getLocation(gameState, id); //location unknown - move randomly
        
        int amtLocs;
        LocationID *adj = connectedLocations(&amtLocs, getLocation(gameState,id), id, round, ANY, g);
        //Note: Dracula cannot visit any location currently in his trail - hunters should not visit target itself!
        while (adj[rand() % amtLocs] == target) move = adj[rand() % amtLocs];
    }
    if (move == CASTLE_DRACULA && camper) { //don't double up campers!
        LocationID *adj = connectedLocations(&amtLocs, getLocation(gameState,id), id, round, ANY, g);
        while (adj[rand() % amtLocs] == target || adj[rand() % amtLocs] == CASTLE_DRACULA) move = adj[rand() % amtLocs];
    }
        
	registerBestPlay(locations[move], msg);
    destroyGraph(g);
}

