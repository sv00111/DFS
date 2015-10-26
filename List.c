//Shrey Valia
//svalia
//PA5 : List.c - List ADT to make a doubly linked list
//


#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node cursor;
    Node front;
    Node back;
    int cursorIndex;
    int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
    Node N;
    N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}


List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    L->cursor = L->front = L->back = NULL;
    L->cursorIndex = -1;
    L->length = 0;
    return L;
}

void freeList(List* pL){
    
    if(pL!=NULL && *pL!=NULL){
        while( length(*pL) > 0) {
            deleteFront(*pL);
        }
        
        free(*pL);
        *pL = NULL;
    }
}



// Access functions -----------------------------------------------------------

// Returns the length of L.
int length(List L)
{
    return (L->length);
}

// returns the current index of L
int getIndex(List L)
{
    if (L->cursorIndex < 0)
    {
        return -1;
    }
    else
        return L->cursorIndex;
}

// Returns the value at the front of L.
int front(List L)
{
    if (length > 0)
    {
        return L->front->data;
    }
    printf("front function called on lisst length <= 0");
    exit(1);
}


// Returns the value at the back of L.
int back(List L)
{
    
    if (length > 0)
    {
        return L->back->data;
    }
    printf("back function called on lisst length <= 0");
    exit(1);
}

// Pre: length(L) != 0, index ! = -1
int getElement(List L)
{
    if (length(L)>0 && getIndex(L)>=0)
    {
        return L->cursor->data;
    }
    fprintf(stderr, "Cursor is undefined\n");
    exit(1);
}

// Returns true (1) if A is equal to B, otherwise returns false (0)
int equals(List A, List B)
{
    int flag  = 1;
    Node N = A->front;
    Node M = B->front;
    
    if(length(A)==length(B)){
        while( flag && N!=NULL){
            if(N->data==M->data)
            {
                flag = 1;
            }
            else
                flag = 0;
            N = N->next;
            M = M->next;
        }
        
        return flag;
    }
    else{
        printf("equals function pre condition not met");
        exit(1);
    }
}


//Manupilation

// Clears L so that it is an empty list.
void clear(List L)
{
    if( L==NULL ){
      		printf("List Error: calling clear() on NULL List reference\n");
      		exit(1);
    }
    
    Node node = L->front;
    while(node->next != NULL)
    {
        node = node->next;
        freeNode(&node->previous);
    }
    freeNode(&node);
    L->front = L->cursor = L->back = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}


//Moves the cursor to index i in list L.
void moveTo(List L, int i)
{
    if(0<=i && i <=(length(L)-1))
    {
        L->cursor = L->front;
        L->cursorIndex = i;
        int j;
        for(j = 0; j < L->cursorIndex; j++)
        {
            L->cursor = L->cursor->next;
        }
        return;
    }
    L->cursorIndex = -1;
    L->cursor = NULL;
}

//Moves the cursor from its current index to the previous index.
void movePrev(List L)
{
    if (0 < getIndex(L) && getIndex(L) <= (length(L) - 1)) {
        L->cursor =L->cursor->previous;;
        L->cursorIndex--;
        return;
    }
    else
    {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
}


//Moves the cursor from its current index to the previous index.
void moveNext(List L)
{
    if(0<=getIndex(L) && getIndex(L) <(length(L)-1))
    {
        L->cursor = L->cursor->next;
        L->cursorIndex++;
        return;
    }
    else {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
}

//Inserts data at the beginning of L.
void prepend(List L, int data){
    Node node = newNode(data);
    if( length(L) == 0 ) {
        L->front = L->back = node;
    }
    else {
        node->next = L->front;
        L->front = node;
        L->front->next->previous = node;
        if (L->cursorIndex >= 0) {
            L->cursorIndex++;
        }
    }
    L->length++;
}


//Inserts data at the end of L.
void append(List L, int data){
    Node node = newNode(data);
    if( length(L) == 0 ) {
        L->front = L->back = node;
        
    }
    else {
        node->previous = L->back;
        L->back = node;
        L->back->previous->next = node;
        node->next = NULL;
    }
    L->length++;
}



//Inserts data before the current position in L.
void insertBefore(List L, int data){
    if(length(L)>0 && getIndex(L)>=0)
    {
        Node node = newNode(data);
        if (L->cursor == L->front) {
            L->front = node;
            node->next = L->cursor;
            L->cursor->previous = node;
            L->length ++;
            L->cursorIndex ++;
        }
        else {
            L->cursor->previous->next = node;
            node->previous = L->cursor->previous;
            node->next = L->cursor;
            L->cursor->previous = node;
            L->length ++;
            L->cursorIndex ++;
        }
        
    }
    else if (getIndex(L) <0) {
        printf("List Error: calling insertBefore() with null index\n");
      		exit(1);
    }
    else
    {
        printf("List is Null\n");
      		exit(1);
    }
}


//inserts data after the current position in L.
void insertAfter(List L, int data)
{
    if(length(L)>0 && getIndex(L)>=0)
    {
        Node node = newNode(data);
        if (L->cursor == L->back) {
            L->back = node;
            node->previous = L->cursor;
            L->cursor->next = node;
            L->length ++;
        }
        else {
            L->cursor->next->previous = node;
            node->next = L->cursor->next;
            node->previous = L->cursor;
            L->cursor->next = node;
            L->length ++;
        }
    }
    else {
        fprintf(stderr, "Cursor is undefined\n");
        exit(1);
    }
}


//Deletes the front element in L.
void deleteFront(List L)
{
    Node node = NULL;
    
    if(L== NULL || length(L) <=0)
    {
        printf("List is NULL or Length is less then 0");
        exit(1);
    }
    node = L->front;
    if(L->length > 1)
    {
        
        L->front = L->front->next;
    }
    else{
        L->front = NULL;
    }
    if(L->cursorIndex == 0)
    {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else
        L->cursorIndex--;
    L->length--;
    
    freeNode(&node);
    
    
}


//Deletes the back element in L.
void deleteBack(List L){
    
    Node node = NULL;
    
    if(length(L) <=0 ||  L== NULL)
    {
        printf("List is undefined");
        exit(1);
    }
    node = L->back;
    if(L->length > 1)
    {
        L->back = L->back->previous;
    }
    else{
        L->back = NULL;
    }
    
    if(L->cursorIndex == 0)
    {
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else
        L->cursorIndex--;
    L->length--;
    
    
    freeNode(&node);
}


//Deletes the current element of L.
void delete(List L)
{
    Node node;
    
    if(L->cursor->next == NULL && length(L)>0 && getIndex(L)>=0)
    {
        node = L->cursor;
        L->cursor->previous->next = NULL;
        L->cursor = NULL;
        L->cursorIndex = -1;
        L->length--;
        freeNode(&node);
    }
    else if(L->cursor->previous == NULL && length(L)>0 && getIndex(L)>=0)
    {
        node = L->cursor;
        L->cursor->next->previous = NULL;
        L->cursor =NULL;
        L->cursorIndex = -1;
        L->length--;
        freeNode(&node);
    }
    else if(length(L)>0 && getIndex(L)>=0) {
        node = L->cursor;
        L->cursor->next->previous = L->cursor->previous;
        L->cursor->previous->next = L->cursor->next;
        L->cursor = NULL;
        L->cursorIndex = -1;
        L->length--;
        freeNode(&node);
    }
}

// Other operations -----------------------------------------------------------

// Prints data elements in L on a single line to out.
void printList(FILE* out, List L)
{
    Node node;// = NULL;
    
    if(L == NULL)
    {
        printf("List error, calling printList on a NULL List");
        exit(1);
    }
    for(node = L->front; node!=NULL; node= node->next)
    {
        fprintf(out, "%d ", node->data);
    }
    
    freeNode(&node);
    
    
}


//Returns a list which is a copy of List L.
List copyList(List L){
    List Q = newList();
    Node N = L->front;
    
    while( N!=NULL ){
        append(Q, N->data);
        N = N->next;
    }
    return Q;
}
