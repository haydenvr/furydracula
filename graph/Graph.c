#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "cities.h"

typedef struct vNode *VList;

struct vNode { 
    Location v;     //ALICANTE etc
    Transport type; //LAND, SEA, ANY
    VList next; 
};  

struct GraphRep { 
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type    
    VList connections[NUM_MAP_LOCATIONS]; // array of lists 
}; 


static void makeMap(Graph g);
static void addLink(Graph g, Location start, Location end, Transport type);

Vlist adjacencies[NUM_MAP_LOCATIONS](Graph g, 

Graph newGraph() { 
    int i; 
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->nV = NUM_MAP_LOCATIONS;
    for (i = 0; i < g->nV; i++){ 
        g->connections[i] = NULL;  
    }
     
    g->nE[LAND] = 0;
    g->nE[SEA] = 0; 
    makeMap(g);
    return g; 
} 

void destroyGraph(Graph g){
    int i;
    VList curr;
    VList next;
    assert(g != NULL);
    assert(g->connections != NULL);
  
    for (i = 0; i < g->nV; i++){         
         curr = g->connections[i];
         while(curr !=NULL){
             next = curr->next;
             free(curr);
             curr=next;
         }
    }
    free(g);
}   


static void addLink(Graph g, Location start, Location end, Transport type){
    //TODO IMPLEMENT THIS FOR TASK 1
	VList new = malloc(sizeof(struct vNode));
	new->v = end;
	new->type = type;
	new->next = NULL;
	if (g->connections[start] == NULL) {
		g->connections[start] = new;
	} else {
		VList tmp = g->connections[start];
		while (tmp->next != NULL) tmp = tmp->next;
		tmp->next = new;
	}
	g->nE[type]++;
}

static void makeMap(Graph g){
   addLink(g, ALICANTE, GRANADA, LAND);
   addLink(g, ALICANTE, MADRID, LAND);
   addLink(g, ALICANTE, SARAGOSSA, LAND);
   addLink(g, BARCELONA, SARAGOSSA, LAND);
   addLink(g, BARCELONA, TOULOUSE, LAND);  
   addLink(g, BORDEAUX, SARAGOSSA, LAND);
   addLink(g, BORDEAUX, TOULOUSE, LAND); 
   addLink(g, CADIZ, GRANADA, LAND);
   addLink(g, CADIZ, LISBON, LAND);
   addLink(g, CADIZ, MADRID, LAND);
   addLink(g, GRANADA, MADRID, LAND);
   addLink(g, LISBON, MADRID, LAND);
   addLink(g, LISBON, SANTANDER, LAND);
   addLink(g, MADRID, SANTANDER, LAND);
   addLink(g, MADRID, SARAGOSSA, LAND); 
   addLink(g, SANTANDER, SARAGOSSA, LAND);
   addLink(g, SARAGOSSA, TOULOUSE, LAND); 
  
   addLink(g, ALICANTE, MEDITERRANEAN_SEA, SEA); 
   addLink(g, ATLANTIC_OCEAN, BAY_OF_BISCAY, SEA);
   addLink(g, ATLANTIC_OCEAN, CADIZ, SEA);
   addLink(g, ATLANTIC_OCEAN, LISBON, SEA);
   addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
   addLink(g, BARCELONA, MEDITERRANEAN_SEA, SEA); 
   addLink(g, BAY_OF_BISCAY, BORDEAUX, SEA);
   addLink(g, BAY_OF_BISCAY, SANTANDER, SEA);
}

//Useful for debugging
void showGraph(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d + %d\n", g->nV, g->nE[LAND],g->nE[SEA]); 
    int i; 
    for (i = 0; i < g->nV; i++) { 
        VList n = g->connections[i]; 
        while (n != NULL) { 
            printf("%d-%d ",i,n->v); 
            if(n->type == LAND){
                printf("L ");
            } else if(n->type == SEA){
                printf("S ");
            } else {
                printf("ERROR NO SUCH TYPE");
                exit(0);
            }
            n = n->next; 
        } 
        if (g->connections [i] != NULL) 
            printf("\n"); 
        } 
} 

int numV(Graph g){
    assert(g != NULL);
    return g->nV;
}

int numE(Graph g, Transport type){
    assert(g != NULL);
    assert(type >= 0 && type <= ANY);
    if(type == ANY){
        return g->nE[LAND] + g->nE[SEA];
    } else {
        return g->nE[type];
    }
}

//returns 1 if there is an edge from start to end of the given type
//gives 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type){
    //TO IMPLEMENT FOR TASK 2
	VList tmp = g->connections[start];
	int found = 0; //NO
	while (tmp != NULL) {
		if (type == ANY) type = tmp->type;
		if ((tmp->v == end)&&(type==tmp->type)) found = 1;
		tmp = tmp->next;
	}
    	return found;
}


//Determines which locations can be reached from the start location
//in n hops or less with a given transport type
//If a location can be reached in n hops or less locs[location] is set to 1
//otherwise it is left as 0
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]){
   //IMPLEMENT FOR TASK 3
	int visited[NUM_MAP_LOCS], i = 0;
	for (i = 0; i < NUM_MAP_LOCS; i++) {
		visited[i] = 0;
	}
	Queue q = newQueue();
	QueueJoin(q, start);
	while (!QueueIsEmpty(q)) {
		
	}
}
