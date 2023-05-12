#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if (pq->capac == 0 || pq->size == 0)
        return NULL;
    return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
    int indexAux = pq->size;
    pq->size++;

    if (pq->size == pq->capac)
    {
        pq->capac *= 2;
        pq->capac++;
        pq->heapArray = (heapElem *) realloc(pq->heapArray, sizeof(heapElem) * pq->capac);
    }
    
    while (1)
    {
        if (indexAux == 0)    break;
        
        if (priority > pq->heapArray[(indexAux - 1) / 2].priority)
        {
            pq->heapArray[indexAux] = pq->heapArray[(indexAux - 1) / 2];
            indexAux = (indexAux - 1) / 2;
        }
        else
            break;
    }
    
    pq->heapArray[indexAux].data = data;
    pq->heapArray[indexAux].priority = priority;
}


void heap_pop(Heap* pq){
    if (pq->size == 0) return;
    heapElem elemAux = pq->heapArray[pq->size - 1];
    pq->heapArray[pq->size - 1] = pq->heapArray[0];
    pq->heapArray[0] = elemAux;
    pq->heapArray[pq->size - 1].priority = 0;
    
    int indexAux = 0;
    int indexHijoMayor = -1;

    
    while (1)
    {
        if (indexAux >= pq->capac)    break;
        if (pq->heapArray[indexAux * 2 + 2].priority > pq->heapArray[indexAux * 2 + 1].priority)
            indexHijoMayor = indexAux * 2 + 2;
        else
            indexHijoMayor = indexAux * 2 + 1;
        
        if (pq->heapArray[indexAux].priority < pq->heapArray[indexHijoMayor].priority)
        {
            elemAux = pq->heapArray[indexAux];
            pq->heapArray[indexAux] = pq->heapArray[indexHijoMayor];
            pq->heapArray[indexHijoMayor] = elemAux;
            indexAux = indexHijoMayor;
        }
        else
            break;
    }
    
    pq->size--;
}

Heap* createHeap(){
    Heap* newHeap = NULL;
    newHeap = (Heap*) malloc(sizeof(Heap));
    if (newHeap == NULL) return NULL;
    newHeap->capac = 3;
    newHeap->size = 0;
    newHeap->heapArray = (heapElem*) malloc(sizeof(heapElem) * newHeap->capac);
    if (newHeap->heapArray == NULL) return NULL;
    for (int i = 0; i < newHeap->capac; i++)
    {
        newHeap->heapArray[i].data = NULL;
        newHeap->heapArray[i].priority = 0;
    }
    return newHeap;
}
