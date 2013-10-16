#include "game.h"
#include "HunterView.h"
#include "hunter.h"
#include "Graph.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_HUNTERS (NUM_PLAYERS - 1)

void decideMove (HunterView gameState) {
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
    
    //continue camping if no other current campers
    if (move == CASTLE_DRACULA) {
        if (camper) move = KLAUSENBURG;
    } else {
        if (!camper) {
            //if no camper and hunter is shortest dist to castle dracula, move towards castle dracula
            int hunterDist[NUM_HUNTER] = {-1,-1,-1,-1};
            int closestHunter = PLAYER_LORD_GODALMING;
            LocationID adj;
            for (i = PLAYER_LORD_GODALMING; i < NUM_HUNTERS; i++) {
                hunterDist[i] = findShortestPath(gameState, getLocation(gameState, i), CASTLE_DRACULA, path, ANY);
                if (hunterDist[closestHunter] > hunterDist[i] || hunterDist[closestHunter] = -1) adj = path[1];
            }
        }       
        //TODO - other moves
    }
/*
            int amtLocs;
			LocationID *adj = connectedLocations(gameState, &amtLocs, getLocation(gameState,id), id, round, 1, 0, 0);
			move = adj[rand() % amtLocs];
*/
	registerBestPlay(locations[move], msg);
}

