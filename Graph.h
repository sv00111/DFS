
//Shrey Valia
//svalia
//PA5 : Graph.h - header file for graph adt.
//

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef DFS_GRAPH_h
#define DFS_GRAPH_h


#define UNDEF -1
#define NIL 0


// private Graph type
typedef struct GraphObj* Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);

/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: getLength(S)==getOrder(G) */
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);




#endif

