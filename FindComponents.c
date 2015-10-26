
//Shrey Valia
//svalia
//PA5 : FindComponents.c - File that imports input file and runs DFS on graph and prints graph and strongly connected components
//



#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
#define MAX_LEN 256

int main(int argc, const char * argv[]) {
    
    char buffer[MAX_LEN];
    
    
    //checks for correct usage
    if( argc != 3 ){
        printf("Usage: Lex <input file> <output file>\n");
        exit(1);
    }
    
    // Check to see if input is open
    // opens the file
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    // checks if files have been open and or created
    if(input == NULL){
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    } else if (output == NULL){
        printf("Unable to open file %s\n", argv[2]);
        return 1;
    }
    
    char numOfVerticesChar[MAX_LEN];
    int numOfVertices;
    
    fgets (numOfVerticesChar, MAX_LEN, input);
    
    numOfVertices = atoi(numOfVerticesChar);
    
    
    Graph graph = newGraph(numOfVertices);
    
    
    while( fgets(buffer, MAX_LEN, input) != NULL) {
        
        int numOne = 0;
        int numTwo = 0;
        sscanf(buffer, "%d %d", &numOne, &numTwo);
        if(numOne == 0 && numTwo == 0)
            break;
        
        addArc(graph, numOne, numTwo);
    }
    
    fprintf(output, "Adjacency list representation of G:\n");
    
    printGraph(output, graph);
    
    fprintf(output,"\n");

    List S = newList();
    int i;
    for(i = 1; i <=numOfVertices; i++)
    {
        append(S, i);
    }
    
    
    DFS(graph, S);
    
    
    Graph graphTrans = transpose(graph);
    
    
    DFS(graphTrans, S);
    
    
    
    List connectedComp = newList();
    int counter = 0;
    for(moveTo(S,length(S)-1); getIndex(S) != -1; movePrev(S))
    {
        prepend(connectedComp, getElement(S));
        if(getParent(graphTrans,getElement(S)) == 0)
        {
            counter ++;
            clear(connectedComp);
        }
        
    }
    
    fprintf(output, "G contains %i strongly connected components: \n", counter);

    counter = 0;
    
    for(moveTo(S,length(S)-1); getIndex(S) != -1; movePrev(S))
    {
        prepend(connectedComp, getElement(S));
        if(getParent(graphTrans,getElement(S)) == 0)
        {
            counter ++;
            fprintf(output, "Component %i: ", counter);
            
            for(moveTo(connectedComp,0); getIndex(connectedComp) != -1; moveNext(connectedComp))
            {
                fprintf(output, "%d ",getElement(connectedComp));
                
            }
            clear(connectedComp);
            fprintf(output, "\n");
        }
    }
    
    
    fclose(input);
    fclose(output);
    
    
    freeGraph(&graphTrans);
    freeGraph(&graph);
    freeList(&S);
    freeList(&connectedComp);
    
    
    
    return 0;
}

