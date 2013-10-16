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

static int dijkstras (Graph g,Location src, Location dest,Location path[],Transport type);

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
    tmp = g->connections[end];
    if (tmp == NULL) g->connections[end] = newNode;
    else {
        for (; tmp->next != NULL; tmp = tmp->next);
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
            if (st[tmp->v] == -1 && dist(st, e) < n && ((tmp->type == type || type == ANY))) {
                st[tmp->v] = e;
                QueueJoin(q, tmp->v, 0);
                locs[tmp->v] = 1;
            }  
        }
    }
    dropQueue(q);
}

int findShortestPath(Location src, Location dest,Location path[],Transport type){
	Graph g = newGraph();
	int a = dijkstras(g, src, dest, path, type);
	if (a != -1) return a;
	//function only checks in one direction, so need to check both in the case that the normal
	//direction doesn't work
	Location tmp[NUM_MAP_LOCATIONS];
	a = dijkstras (g, dest, src, tmp, type);
	int i, b = 0;
    for(i = a-1; i >= 0; i--){
               path[b] = tmp[i];
               b++;
    }
	return a;
}
	
static int dijkstras (Graph g,Location src, Location dest,Location path[],Transport type){
	int v, w, alt, dist[g->nV], visited[g->nV], maxWT = 9999, *edges,amtConsider; //st visited, wt dist //,
	Queue q = newQueue();;
	for (v = 0; v < g->nV; v++)
		if (v == src) { dist[v] = 0; QueueJoin(q,v,0); visited[v] = -1; }
		else { dist[v] = maxWT; QueueJoin(q,v,maxWT); visited[v] = -1;  }
	while (!QueueIsEmpty(q)) {
		// get vertex with lowest weight
		v = QueueLeaveMin(q);
		if (dist[v] != maxWT) {
			edges = connectedLocations(&amtConsider, v,PLAYER_LORD_GODALMING,0,type); //note player doesn't matter
			for (w = 0; w < amtConsider; w++) {
				if (isAdjacent(g, v, edges[w], type)) {
				    //printf("hi this is adjacent %d to %d\n",v,w);
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
Item QueueLeaveMin(Queue Q) {
	int i = 1,n = 0, currVal;
	Node curr = Q->head;
	currVal = curr->dist;
	curr = curr->next;
	while (curr != NULL) {
		if (curr->dist < currVal) { currVal = curr->dist; n = i; }
		i++;
		curr = curr->next;
	}
	return QueueLeave(Q, n);
}

// remove nth item from front of Queue
Item QueueLeave(Queue Q, int n)
{
	assert(Q != NULL);
	assert(Q->head != NULL);
	Item it;
    Node old, prev;
	if (n == 0) {
		it = Q->head->value;
		old = Q->head;
		Q->head = old->next;
		if (Q->head == NULL)
			Q->tail = NULL;
	} else {
		int i = 0;
		old = Q->head;
        prev = NULL;
		while ((i < n)&&(old != NULL)) {
			prev = old;			
			old = old->next;
			i++;
		}
		if (old == NULL) return -1;
		prev->next = old->next;
		it = old->value;
		if (prev->next == NULL) Q->tail = prev;
	}
	//printf("the valuuususus %d\n",old->dist);
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

