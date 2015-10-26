
//Shrey Valia
//svalia
//PA5 : Graph.c - Graph ADT to make and run DFS on graph.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//#include "List.c"

#define White -1
#define Black 1
#define Gray 0


typedef struct GraphObj{
    
    List *arrayOfLists;
    int *color;
    int *parents;
    
    int *discover;
    int *finish;
    
    int graphOrder; //# of vertix
    int graphSize; //# number of edges
    
} GraphObj;


Graph newGraph(int n)
{

	if(n < 0)
{
	printf("error: n is a negative number in newGraph");
	exit(1);
}
    Graph newGraph = malloc(sizeof(struct GraphObj));
    
    newGraph->arrayOfLists = calloc(n+1,sizeof(List));
    
    newGraph->color = calloc(n+1,sizeof(int));
    
    newGraph->parents = calloc(n+1,sizeof(int));
    newGraph->discover = calloc(n+1,sizeof(int));
    newGraph->finish = calloc(n+1,sizeof(int));
    newGraph->graphOrder = n;
    newGraph ->graphSize = 0;
    int i = 0;
    for (i = 0; i < n+1; i++)
    {
        newGraph->arrayOfLists[i] = newList();
        newGraph->color[i] = White;  //because all the vertices are white, havent been asinged yet
        newGraph -> parents[i] = NIL; // no source yet
        newGraph ->discover[i] = UNDEF; //no distance yet;
        newGraph ->finish[i] = UNDEF; //no distance yet;
        
        
    }
    return newGraph;
}

void freeGraph(Graph* pG)
{
    
    if(pG!=NULL && *pG!=NULL){
        int i = 0;
        for( i = 0; i < ((*pG)->graphOrder) + 1; i++){
            freeList(&((*pG)->arrayOfLists[i]));
        }
        
        
        free((*pG)->arrayOfLists);
        (*pG)->arrayOfLists = NULL;
        
        free((*pG) -> color);
        free((*pG) -> parents);
        free((*pG) -> discover);
        free((*pG) -> finish);
        
        
        free((*pG));
        
        *pG = NULL;
    }
}



/*** Access functions ***/
int getOrder(Graph G)
{
    return G->graphOrder;
}

int getSize(Graph G)
{
    return G->graphSize;
}

int getParent(Graph G, int u)
{
    if(u > 0 && u <= getOrder(G))
        return G->parents[u];
    else
    {
        printf("invalid parameters for vertex");
        exit(1);
    }
}
int getDiscover(Graph G, int u)//Pre: 1<=u<=n=getOrder(G)
{
    if(1<=u || u<=getOrder(G)|| G->graphSize==getOrder(G))
    {
        return G->discover[u];
    }
    else
    {
        printf("(discover)invalid parameters for ");
        exit(1);
    }

}

int getFinish(Graph G, int u) /* Pre: 1<=u<=n=getOrder(G) */
{
 
    if(1<=u || u<=getOrder(G)|| G->graphSize==getOrder(G))
    {
        return G->finish[u];
    }
    else
    {
        printf("(finish)invalid parameters for ");
        exit(1);
    }
}



void addArc(Graph G, int u, int v)
{
    if(u > 0 && u <= getOrder(G) && v > 0&& v <= getOrder(G) )
    {
        if (length(G->arrayOfLists[u]) == 0){
            append(G->arrayOfLists[u], v);
        }
        else {
            for(moveTo(G->arrayOfLists[u], 0); getIndex(G->arrayOfLists[u]) >= 0; moveNext(G->arrayOfLists[u])){
                int cursor = getElement(G->arrayOfLists[u]);
                if(v < cursor){
                    insertBefore(G->arrayOfLists[u], v);
                    break;
                }
            }
            if(getIndex(G->arrayOfLists[u]) == -1){
                append(G->arrayOfLists[u], v);
            }
        }
        
        G->graphSize++;
    }
    else
    {
        printf("both vertex arent greater then 0");
        exit(1);
    }
}

void addEdge(Graph G, int u, int v)
{
    //Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. Your program is required to maintain these lists in sorted order by increasing vertex labels
    
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("both vertex arent greater then 0");
    }
    
    addArc(G,u, v);
    addArc(G,v, u);
    G->graphSize--;
}

void DFS_Visit(Graph G, int index, List S, int *time)
{
    (*time) = (*time)+1;
    G->discover[index] = *time;
    G->color[index] = Gray;
    
    
    List adj = G->arrayOfLists[index];
    
    moveTo(adj, 0);
    
    for (; getIndex(adj) != -1; moveNext(adj)) {
        
        int x = getElement(adj);
        if (G->color[x] == White) {
            G->parents[x] = index;
            DFS_Visit(G, x, S, time);
        }
    }
    
    
    G->color[index] = Black;
    (*time)++;
    G->finish[index] = *time;
    prepend(S,index);
}


void DFS(Graph G, List S)
{
    if(length(S)==getOrder(G))
    {
        int i;
        for (i = 1; i < G->graphOrder+1; i++){
            
            G->color[i] = White;
            G->discover[i] = UNDEF;
            G->finish[i] = UNDEF;
            G->parents[i] = NIL;
        }
//
        List L = copyList(S);
        clear(S);

    
        int time = 0;
        
        
        //for each vertex u in G:V
        for (moveTo(L, 0); getIndex(L)!= -1; moveNext(L)){
            int index = getElement(L);
            if((G->color[index]) == White)
            {
                DFS_Visit(G, index, S, &time);
            }
        }

        freeList(&L);
    
    }
    else
    {
        printf("length and order arent same, prereqs not met in dfs");
        exit(1);
    }
    
}


Graph transpose(Graph G)
{
    Graph transpose = newGraph(G->graphOrder);
    transpose->graphSize = G->graphSize;
    
    for(int i = 1; i < getOrder(G)+1; i++)
    {
        List L = G->arrayOfLists[i];
        for(moveTo(L, 0); getIndex(L) != -1; moveNext(L))
        {
            append(transpose->arrayOfLists[getElement(L)], i);
        }
       // freeList(&L);
    }
    
    
    return transpose;
}

Graph copyGraph(Graph G)
{
    Graph copy = newGraph(getOrder(G));
    copy->graphSize = G->graphSize;
    
    for (int i = 1; i < getOrder(G)+1; i++){
        List L = G->arrayOfLists[i];
        for(moveTo(L, 0); getIndex(L) != -1; moveNext(L))
        {
            append(copy->arrayOfLists[i], getElement(L));
        }

    }
    
    
    return copy;
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G)
{
    if(out == NULL || G == NULL){
        printf("Passed in NUll parameters");
        exit(1);
    }
    
    for (int i = 1; i < getOrder(G) + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->arrayOfLists[i]);
        fprintf(out, "\n");
    }
    
}



