#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "connections_v1.2.h"
#include "Graph.h"
#include "HunterView.h"

struct vNode { 
    Location v;     //ALICANTE etc
    Transport type; //ROAD, SEA, ANY
    VList next; 
};  

struct GraphRep { 
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type    
    VList connections[NUM_MAP_LOCATIONS]; // array of lists 
}; 

typedef struct QueueNode {
	Item value;
	struct QueueNode *next;
	Item dist;
} QueueNode;

typedef struct QueueRep {
	QueueNode *head;  // ptr to first node
	QueueNode *tail;  // ptr to last node
} QueueRep;

typedef struct QueueNode *Node;

static int dijkstras (Graph g,Location src, Location dest,Location path[],Transport type, int round);

Graph newGraph() { 
    int i; 
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->nV = NUM_MAP_LOCATIONS;
    for (i = 0; i < g->nV; i++){ 
        g->connections[i] = NULL;  
    }
     
    g->nE[ROAD] = 0;
    g->nE[RAIL] = 0; 	
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


void addLink(Graph g, Location start, Location end, Transport type){
    VList newNode = malloc(sizeof(struct vNode));
    newNode->v = end;
    newNode->type = type;
	newNode->next = NULL;
    g->nE[type]++;
    VList tmp = g->connections[start];
    if (tmp == NULL) g->connections[start] = newNode;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = newNode;
    }
    
    newNode = malloc(sizeof(struct vNode));
    newNode->v = start;
    newNode->type = type;
	newNode->next = NULL;
    tmp = g->connections[end];
	int i = 0;
    if (tmp == NULL) g->connections[end] = newNode;
    else {
        for (; tmp->next != NULL; tmp = tmp->next) { i++; }
        tmp->next = newNode;
    }
}

//Useful for debugging
void showGraph(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d + %d\n", g->nV, g->nE[ROAD],g->nE[SEA]); 
    int i; 
    for (i = 0; i < g->nV; i++) { 
        VList n = g->connections[i]; 
        while (n != NULL) { 
            printf("%d-%d ",i,n->v); 
            if(n->type == ROAD){
                printf("L ");
            } else if (n->type == RAIL) {
				printf("R ");
			}else if(n->type == SEA){
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
        return g->nE[ROAD] + g->nE[SEA] + g->nE[RAIL];
    } else {
        return g->nE[type];
    }
}

//returns 1 if there is an edge from start to end of the given type
//gives 0 otherwise
int isAdjacent(Graph g, Location start, Location end, Transport type){
	if (start == end) return 1;
    VList tmp = g->connections[start];
    for (; tmp != NULL; tmp = tmp->next) if (tmp->v == end && (tmp->type == type || type == ANY)) return 1;
    return 0;
}


static int dist(int st[], int e) {
    assert(st[e] != -1);
    int count = 0;
    int i = e;
    while (st[i] != i) {
        count++;
        i = st[i];
    }
    return count;
}

//Determines which locations can be reached from the start location
//in n hops or less with a given transport type
//If a location can be reached in n hops or less locs[location] is set to 1
//otherwise it is left as 0
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]){
    Queue q = newQueue();
    int st[NUM_MAP_LOCATIONS];
    int i, e;
    VList tmp;
    for (i = 0; i < NUM_MAP_LOCATIONS; i++) {
        st[i] = -1; 
    }
    st[start] = start;
    locs[start] = 1;
    QueueJoin(q, start,0);
    while (!QueueIsEmpty(q)) {
        e = QueueLeave(q,0);
        for (tmp = g->connections[e]; tmp != NULL; tmp = tmp->next) {
            if (st[tmp->v] == -1 && dist(st, e) < n && (tmp->type == type || type == ANY)) {
                st[tmp->v] = e;
                QueueJoin(q, tmp->v, 0);
                locs[tmp->v] = 1;
            }  
        }
    }
    dropQueue(q);
}

int findShortestPath(Location src, Location dest,Location path[],Transport type, int round){
	Graph g = newGraph();
    int len = dijkstras(g, src, dest, path, type, round);
    destroyGraph(g);
	return len;
}
	
static int dijkstras (Graph g,Location src, Location dest,Location path[],Transport type, int round){
	int v, w, alt, dist[g->nV], visited[g->nV], maxWT = 9999, *edges,amtConsider, haveVisited[g->nV]; //st visited, wt dist //,
	Queue q = newQueue();
	for (v = 0; v < g->nV; v++) { 
		haveVisited[v] = -1;
		if (v == src) { dist[v] = 0; QueueJoin(q,v,0); visited[v] = -1;  }
		else { dist[v] = maxWT; QueueJoin(q,v,maxWT); visited[v] = -1; }
	}
	while (!QueueIsEmpty(q)) {
		// get vertex with lowest weight
		
		v = QueueLeaveMin(q,dist, haveVisited, g->nV);
		haveVisited[v] = 1;
		if (dist[v] != maxWT) {
			edges = connectedLocations(&amtConsider, v,PLAYER_LORD_GODALMING,round,type,g); //note player doesn't matter
			for (w = 0; w < amtConsider; w++) {
				
				//if ((isAdjacent(g, v, edges[w], type))&&(v != edges[w])) {
				if (v != edges[w]) {
				    
					alt = dist[v] + 1;
					if (alt < dist[edges[w]]) { dist[edges[w]] = alt; visited[edges[w]] = v; } //
					//QueueJoin(q,w,dist[w]);
					
				}
				
			}
			
		}
	}
	v = dist[dest]; 
	int curr = dest;
	if (v == maxWT) return -1;
	while (v >= 0) { path[v] = curr; curr = visited[curr]; v--; } 
	dropQueue(q);
	return dist[dest] + 1;
}

//
//QUEUE IMPLEMENTATION
//

// create new empty Queue
Queue newQueue()
{
	Queue q;
	q = malloc(sizeof(QueueRep));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	return q;
}

//find smallest item in Queue, remove it, and return it's value
Item QueueLeaveMin(Queue Q, int *dists, int *visited, int amt) {
	int i, n = 0, currVal = 9999; 
	Node tmp = Q->head;
	while (tmp != NULL) {
		i = tmp->value;
		if ((dists[i] < currVal)&&(visited[i] == -1)) { currVal = dists[i]; n = i; }
		tmp = tmp->next;
	}
	return QueueLeave(Q, n); //note need to change Queue leave for it to make the queue to leave by value not index
}

// remove nth item from front of Queue
Item QueueLeave(Queue Q, int n)
{
	assert(Q != NULL);
	assert(Q->head != NULL);
	Item it;
    Node old = Q->head, prev = NULL;
    int i = 0;
	for (;i < n; i++) {
	    if (old->next == NULL) break;
	    prev = old; 
	    old = old->next;
	}	
	if (prev == NULL) {
		//pull out head
		old = Q->head;
		Q->head = old->next;
		if (Q->head == NULL)
			Q->tail = NULL;
	} else {
		prev->next = old->next;
		if (prev->next == NULL) Q->tail = prev;
	}
	it = old->value;
	free(old);
	return it;
}

// free memory used by Queue
void dropQueue(Queue Q)
{
	QueueNode *curr, *next;
	assert(Q != NULL);
	// free list nodes
	curr = Q->head;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	// free queue rep
	free(Q);
}

// add item at end of Queue 
void QueueJoin(Queue Q, Item it, Item dist)
{
	assert(Q != NULL);
	Node new = malloc(sizeof(QueueNode));
	assert(new != NULL);
	new->value = it;
	new->dist = dist;
	new->next = NULL;
	if (Q->head == NULL)
		Q->head = new;
	if (Q->tail != NULL)
		Q->tail->next = new;
	Q->tail = new;
}

// check for no items
int QueueIsEmpty(Queue Q)
{
	return (Q->head == NULL);
}
