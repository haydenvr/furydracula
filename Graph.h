#ifndef GRAPH_H
#define GRAPH_H

#define ROAD 0
#define RAIL 1
#define SEA 2
#define ANY 3
#define NUM_TRANSPORT 3


// vertices denoted by integers 0..N-1 
typedef int Location;
typedef int Transport; 
typedef struct vNode *VList;
typedef struct QueueRep *Queue;
typedef int Item;

typedef struct edge{
    Location start;
    Location end;
    Transport type;
} Edge;

// graph representation is hidden 
typedef struct GraphRep *Graph; 

// operations on graphs 
Graph newGraph();  
void destroyGraph(Graph g); 
void showGraph(Graph g); 

int numV(Graph g);
int numE(Graph g, Transport t);


//returns 1 if there is an edge from start to end with a given transport type
//returns 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type);

//Determines which locations can be reached from the start location
//in n hops or less with a given transport type
//If a location can be reached in n hops or less locs[location] is set to 1
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]);

void makeMap(Graph g);
void addLink(Graph g, Location start, Location end, Transport type);
Queue newQueue(); // create new empty queue
void dropQueue(Queue); // free memory used by queue
void QueueJoin(Queue Q, Item it, Item dist); // add item on queue
Item QueueLeave(Queue, int); // remove item from queue
int QueueIsEmpty(Queue); // check for no items
Item QueueLeaveMin(Queue Q, int *dists, int *visited, int amt); //return smallest val in queue
int findShortestPath(Location src, Location dest,Location path[],Transport type, int round); //return number of locs in path

#endif
