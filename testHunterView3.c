#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cities.h"
#include "game.h"
#include "HunterView.h"

#define MAX_LOCATION 71

void haydenTestFunc();
void julianTestFunc();

//TeamSegItsYourFault's test program HunterView.h
int main() {
	printf("Testing with Hayden's tests\n");
    haydenTestFunc();
	printf("Passed Hayden's tests!\nNow testing with Julian's tests\n");
	julianTestFunc();
	printf("Passed Julian's tests!\nCongrats, all tests passed!\n");
	return 0;
}

void haydenTestFunc() {
	int i;
	playerMessage messages[] = {};
	printf("Testing two moves in round 0\n");
	HunterView hv = newHunterView("GVA.... SSA....", messages);
	assert(getCurrentPlayer(hv) == PLAYER_VAN_HELSING);
	assert(getRound(hv) == 0);
	assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
	assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == GAME_START_SCORE);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == VALONA);
        
    printf("passed basic move test\n");
	disposeHunterView(hv);
	
        playerMessage messages2[] = {"Hello","Rubbish","Stuff","","Mwahahah"};
	printf("Testing score loss when vampire matures and running into a trap\n");
	hv = newHunterView("GSZ.... SRO.... HSNT... MFL.... DC?..V.", messages2);
	assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
	assert(getRound(hv) == 1);
	assert(getLocation(hv, PLAYER_LORD_GODALMING) == SZEGED);
	assert(getLocation(hv, PLAYER_DR_SEWARD) == ROME);
	assert(getLocation(hv, PLAYER_VAN_HELSING) == SANTANDER);
	assert(getLocation(hv, PLAYER_MINA_HARKER) == FLORENCE);
    assert(getLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
	assert(getHealth(hv,PLAYER_VAN_HELSING) == GAME_START_HUNTER_LIFE_POINTS- LIFE_LOSS_TRAP_ENCOUNTER);
	assert(getScore(hv) == GAME_START_SCORE - SCORE_LOSS_VAMPIRE_MATURES);
	printf("passed testing vampire matures and trap\n");
    disposeHunterView(hv);
        

	printf("Test for encountering Dracula and hunter history\n");
        playerMessage messages3[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!"};
	hv = newHunterView("GST.... SAO.... HCD.... MAO.... DGE.... GGED...", messages3);
	assert(getLocation(hv,PLAYER_DRACULA) == GENEVA);
	assert(getHealth(hv, PLAYER_LORD_GODALMING) == 5);
	assert(getHealth(hv,PLAYER_DRACULA) == 30);
	assert(getLocation(hv, PLAYER_LORD_GODALMING) == GENEVA);
        LocationID history[TRAIL_SIZE];
	getHistory(hv, PLAYER_DRACULA,history);
        assert(history[0] == GENEVA);
        assert(history[1] == UNKNOWN_LOCATION);
        getHistory(hv, PLAYER_LORD_GODALMING,history);
        assert(history[0] == GENEVA);
        assert(history[1] == STRASBOURG);
        assert(history[2] == UNKNOWN_LOCATION);
        getHistory(hv,PLAYER_DR_SEWARD,history);
        assert(history[0] == ATLANTIC_OCEAN);
        assert(history[1] == UNKNOWN_LOCATION);
        printf("passed\n");        
	disposeHunterView(hv);


	printf("Test for dracula doubling back at sea, and losing blood points\n");
	playerMessage messages4[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Back I go"};
        hv = newHunterView("GGE.... SGE.... HGE.... MGE.... DS?.... GST.... SST.... HST.... MST.... DD1....", messages4);
        
        assert(getLocation(hv,PLAYER_DRACULA) == DOUBLE_BACK_1);
        getHistory(hv,PLAYER_DRACULA,history);
        assert(history[0] == DOUBLE_BACK_1);
	assert(history[1] == SEA_UNKNOWN);
	assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 4);
	assert(getCurrentPlayer(hv) == 0);
        printf("passed\n");
	disposeHunterView(hv);


	printf("Test for connections\n");
	int seen[MAX_LOCATION], *edges;
	hv = newHunterView("", messages);	
	
        int size;
	edges = connectedLocations(hv,&size, GALATZ,PLAYER_LORD_GODALMING,0,1,0,0);
	memset(seen, 0, MAX_LOCATION*sizeof(int));
	for (i = 0; i< size ; i++) {
		seen[edges[i]] = 1;
	}
        assert(seen[GALATZ]);
	assert(seen[CONSTANTA] && seen[BUCHAREST] && seen[KLAUSENBURG] && seen[CASTLE_DRACULA]);
	assert(size == 5);
        free(edges);
	printf("Test for self passed!\nNow testing Sea connections\n");
	//Checking Ionian seas
        edges = connectedLocations(hv, &size,IONIAN_SEA, PLAYER_LORD_GODALMING, 0 , 0, 0, 1);
	memset(seen, 0, MAX_LOCATION*sizeof(int));
	for (i = 0; i < size; i++) {
		seen[edges[i]] = 1;
	}
	assert(seen[IONIAN_SEA] && seen[BLACK_SEA] && seen[ADRIATIC_SEA] && seen[TYRRHENIAN_SEA]);
        assert(seen[ATHENS] && seen[VALONA] && seen[SALONICA]);
        assert(size == 7);
        free(edges);
	printf("Test for sea connections passed!\nNow testing rail connections\n");
	edges = connectedLocations(hv, &size,ATHENS,PLAYER_LORD_GODALMING,0,0,1,0);
        assert(size == 1);
        assert(edges[0] == ATHENS);
        free(edges);
        
	printf("Test for rail connection to self passed!\nNow testing rail connections Barcelona\n");
	edges = connectedLocations(hv, &size,BARCELONA,PLAYER_LORD_GODALMING,1,0,1,0);
    assert(size == 3);
    free(edges);
	printf("Test for rail connections passed!\nCongrats, all tests passed!\n");
    disposeHunterView(hv);
}

void julianTestFunc() {

}