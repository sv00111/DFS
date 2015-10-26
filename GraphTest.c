//Shrey Valia
//svalia
//PA5 : GraphTest.c - Test module I wrote that isolates and tests Graph.c



#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
    int i, n=30;
    List S = newList();
    Graph G = newGraph(n);
    Graph T=NULL, C=NULL;
    
    for(i=1; i<=n; i++) append(S, i);
    
    for (i = 1; i < 7; i++)
    {
        if(i%2)
        {
            addArc(G, i,i+1);

        }
    }
    
    for (i = 1; i < 7; i++)
    {
        if(i%3 && i > 2)
        {
            addArc(G, i,i-2);
            
        }
        else
        {
            addArc(G, i,i);
        }
        
    }
    
    for(i=7; i<n; i++){
        if (i <= 20)
        {
            addArc(G, 6, i);
        }
        if( i%7)
            addArc(G, i, i+1);
        if( i<=23  )
            addArc(G, i, i+7);
    }
    
    addArc(G, 9, 30);
    addArc(G, 17, 13);
    addEdge(G, 30, 28);

    
    DFS(G, S);
    
    printf("The order of the graph is %i\n", getOrder(G));
    printf("The size of the graph is %i\n", getSize(G));
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }

    
    
    printGraph(stdout, G);

    
    for(i=1; i<=n; i++){
    
        if(getParent(G, i) == NIL)
        {
            printf("the parent for the vertex %i is: NIL \n", i);

        }
        else
            printf("the parent for the vertex %i is: %i \n", i, getParent(G, i));
        
    }
    
    C = copyGraph(G);
    T = transpose(G);
    
    //***** copy graph
    DFS(C, S);
    
    printf("\n");
    
    printf("\n");
    
    printf("copy graph:\n");
    
    printf("The order of the copied graph is %i\n", getOrder(C));
    printf("The size of the copied graph is %i\n", getSize(C));
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(C, i), getFinish(C, i), getParent(C, i));
    }
    
    
    
    printGraph(stdout, C);
    
    for(i=1; i<=n; i++){
        
        if(getParent(C, i) == NIL)
        {
            printf("in the copy graph the parent for the vertex %i is: NIL \n", i);
            
        }
        else
            printf("in the copy graph the parent for the vertex %i is: %i \n", i, getParent(C, i));
        
    }

    printf("\n");
    
    printf("\n");
    
    printf("Transpose graph:\n");
    
    //***** transpose graph
    DFS(T, S);
    
    
    printf("The order of the transpose graph is %i\n", getOrder(T));
    printf("The size of the transpose graph is %i\n", getSize(T));
    
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for(i=1; i<=n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    
    
    
    printGraph(stdout, T);
    
    for(i=1; i<=n; i++){
        
        if(getParent(T, i) == NIL)
        {
            printf("in the transpose graph the parent for the vertex %i is: NIL \n", i);
            
        }
        else
            printf("in the transpose graph the parent for the vertex %i is: %i \n", i, getParent(T, i));
        
    }
    
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);

    return 0;
}




/*
 OUTPUT of the program:The order of the graph is 30
 The size of the graph is 62
 
 x:  d  f  p
 1:  1  4  0
 2:  2  3  1
 3:  5  8  0
 4:  6  7  3
 5:  9 60  0
 6: 10 59  5
 7: 11 20  6
 8: 21 58  6
 9: 22 51  8
 10: 23 46  9
 11: 24 41 10
 12: 25 36 11
 13: 26 31 12
 14: 12 19  7
 15: 52 57  8
 16: 47 50  9
 17: 42 45 10
 18: 37 40 11
 19: 32 35 12
 20: 27 30 13
 21: 13 18 14
 22: 53 56 15
 23: 48 49 16
 24: 43 44 17
 25: 38 39 18
 26: 33 34 19
 27: 28 29 20
 28: 14 17 21
 29: 54 55 22
 30: 15 16 28
 1: 1 2
 2: 2
 3: 3 4
 4: 2
 5: 3 6
 6: 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 7: 14
 8: 9 15
 9: 10 16 30
 10: 11 17
 11: 12 18
 12: 13 19
 13: 14 20
 14: 21
 15: 16 22
 16: 17 23
 17: 13 18 24
 18: 19 25
 19: 20 26
 20: 21 27
 21: 28
 22: 23 29
 23: 24 30
 24: 25
 25: 26
 26: 27
 27: 28
 28: 30
 29: 30
 30: 28
 the parent for the vertex 1 is: NIL
 the parent for the vertex 2 is: 1
 the parent for the vertex 3 is: NIL
 the parent for the vertex 4 is: 3
 the parent for the vertex 5 is: NIL
 the parent for the vertex 6 is: 5
 the parent for the vertex 7 is: 6
 the parent for the vertex 8 is: 6
 the parent for the vertex 9 is: 8
 the parent for the vertex 10 is: 9
 the parent for the vertex 11 is: 10
 the parent for the vertex 12 is: 11
 the parent for the vertex 13 is: 12
 the parent for the vertex 14 is: 7
 the parent for the vertex 15 is: 8
 the parent for the vertex 16 is: 9
 the parent for the vertex 17 is: 10
 the parent for the vertex 18 is: 11
 the parent for the vertex 19 is: 12
 the parent for the vertex 20 is: 13
 the parent for the vertex 21 is: 14
 the parent for the vertex 22 is: 15
 the parent for the vertex 23 is: 16
 the parent for the vertex 24 is: 17
 the parent for the vertex 25 is: 18
 the parent for the vertex 26 is: 19
 the parent for the vertex 27 is: 20
 the parent for the vertex 28 is: 21
 the parent for the vertex 29 is: 22
 the parent for the vertex 30 is: 28
 
 
 copy graph:
 The order of the copied graph is 30
 The size of the copied graph is 62
 
 x:  d  f  p
 1: 59 60  0
 2:  4  5  4
 3:  2  7  5
 4:  3  6  3
 5:  1 58  0
 6:  8 57  5
 7:  9 18  6
 8: 19 56  6
 9: 20 49  8
 10: 21 44  9
 11: 22 39 10
 12: 23 34 11
 13: 24 29 12
 14: 10 17  7
 15: 50 55  8
 16: 45 48  9
 17: 40 43 10
 18: 35 38 11
 19: 30 33 12
 20: 25 28 13
 21: 11 16 14
 22: 51 54 15
 23: 46 47 16
 24: 41 42 17
 25: 36 37 18
 26: 31 32 19
 27: 26 27 20
 28: 12 15 21
 29: 52 53 22
 30: 13 14 28
 1: 1 2
 2: 2
 3: 3 4
 4: 2
 5: 3 6
 6: 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 7: 14
 8: 9 15
 9: 10 16 30
 10: 11 17
 11: 12 18
 12: 13 19
 13: 14 20
 14: 21
 15: 16 22
 16: 17 23
 17: 13 18 24
 18: 19 25
 19: 20 26
 20: 21 27
 21: 28
 22: 23 29
 23: 24 30
 24: 25
 25: 26
 26: 27
 27: 28
 28: 30
 29: 30
 30: 28
 in the copy graph the parent for the vertex 1 is: NIL
 in the copy graph the parent for the vertex 2 is: 4
 in the copy graph the parent for the vertex 3 is: 5
 in the copy graph the parent for the vertex 4 is: 3
 in the copy graph the parent for the vertex 5 is: NIL
 in the copy graph the parent for the vertex 6 is: 5
 in the copy graph the parent for the vertex 7 is: 6
 in the copy graph the parent for the vertex 8 is: 6
 in the copy graph the parent for the vertex 9 is: 8
 in the copy graph the parent for the vertex 10 is: 9
 in the copy graph the parent for the vertex 11 is: 10
 in the copy graph the parent for the vertex 12 is: 11
 in the copy graph the parent for the vertex 13 is: 12
 in the copy graph the parent for the vertex 14 is: 7
 in the copy graph the parent for the vertex 15 is: 8
 in the copy graph the parent for the vertex 16 is: 9
 in the copy graph the parent for the vertex 17 is: 10
 in the copy graph the parent for the vertex 18 is: 11
 in the copy graph the parent for the vertex 19 is: 12
 in the copy graph the parent for the vertex 20 is: 13
 in the copy graph the parent for the vertex 21 is: 14
 in the copy graph the parent for the vertex 22 is: 15
 in the copy graph the parent for the vertex 23 is: 16
 in the copy graph the parent for the vertex 24 is: 17
 in the copy graph the parent for the vertex 25 is: 18
 in the copy graph the parent for the vertex 26 is: 19
 in the copy graph the parent for the vertex 27 is: 20
 in the copy graph the parent for the vertex 28 is: 21
 in the copy graph the parent for the vertex 29 is: 22
 in the copy graph the parent for the vertex 30 is: 28
 
 
 Transpose graph:
 The order of the transpose graph is 30
 The size of the transpose graph is 62
 
 x:  d  f  p
 1:  1  2  0
 2: 59 60  0
 3: 55 56  0
 4: 57 58  0
 5:  3  4  0
 6:  5  6  0
 7: 45 46  0
 8:  7  8  0
 9: 15 16  0
 10: 21 22  0
 11: 27 28  0
 12: 33 34  0
 13: 39 40  0
 14: 47 48  0
 15:  9 10  0
 16: 17 18  0
 17: 23 24  0
 18: 29 30  0
 19: 35 36  0
 20: 41 42  0
 21: 49 50  0
 22: 11 12  0
 23: 19 20  0
 24: 25 26  0
 25: 31 32  0
 26: 37 38  0
 27: 43 44  0
 28: 51 54  0
 29: 13 14  0
 30: 52 53 28
 1: 1
 2: 1 2 4
 3: 3 5
 4: 3
 5:
 6: 5 6
 7: 6
 8: 6
 9: 6 8
 10: 6 9
 11: 6 10
 12: 6 11
 13: 6 12 17
 14: 6 7 13
 15: 6 8
 16: 6 9 15
 17: 6 10 16
 18: 6 11 17
 19: 6 12 18
 20: 6 13 19
 21: 14 20
 22: 15
 23: 16 22
 24: 17 23
 25: 18 24
 26: 19 25
 27: 20 26
 28: 21 27 30
 29: 22
 30: 9 23 28 29
 in the transpose graph the parent for the vertex 1 is: NIL
 in the transpose graph the parent for the vertex 2 is: NIL
 in the transpose graph the parent for the vertex 3 is: NIL
 in the transpose graph the parent for the vertex 4 is: NIL
 in the transpose graph the parent for the vertex 5 is: NIL
 in the transpose graph the parent for the vertex 6 is: NIL
 in the transpose graph the parent for the vertex 7 is: NIL
 in the transpose graph the parent for the vertex 8 is: NIL
 in the transpose graph the parent for the vertex 9 is: NIL
 in the transpose graph the parent for the vertex 10 is: NIL
 in the transpose graph the parent for the vertex 11 is: NIL
 in the transpose graph the parent for the vertex 12 is: NIL
 in the transpose graph the parent for the vertex 13 is: NIL
 in the transpose graph the parent for the vertex 14 is: NIL
 in the transpose graph the parent for the vertex 15 is: NIL
 in the transpose graph the parent for the vertex 16 is: NIL
 in the transpose graph the parent for the vertex 17 is: NIL
 in the transpose graph the parent for the vertex 18 is: NIL
 in the transpose graph the parent for the vertex 19 is: NIL
 in the transpose graph the parent for the vertex 20 is: NIL
 in the transpose graph the parent for the vertex 21 is: NIL
 in the transpose graph the parent for the vertex 22 is: NIL
 in the transpose graph the parent for the vertex 23 is: NIL
 in the transpose graph the parent for the vertex 24 is: NIL
 in the transpose graph the parent for the vertex 25 is: NIL
 in the transpose graph the parent for the vertex 26 is: NIL
 in the transpose graph the parent for the vertex 27 is: NIL 
 in the transpose graph the parent for the vertex 28 is: NIL 
 in the transpose graph the parent for the vertex 29 is: NIL 
 in the transpose graph the parent for the vertex 30 is: 28
*/

