#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"                


ArrayList *createList(void) {
    ArrayList *auxArrayList = NULL;
    auxArrayList = (ArrayList *) malloc(sizeof(ArrayList));
    auxArrayList->data = NULL;
    auxArrayList->data = (void**) malloc(sizeof(void*) * INITIALCAPAC);
    auxArrayList->capacity = INITIALCAPAC;
    auxArrayList->size = 0;
    return auxArrayList;
}

void push(ArrayList * l, void * data, int i){
    if (i >= l->capacity || l->size == l->capacity)
    {
        if (i <= l->capacity)
        {
            l->data = (void **) realloc(l->data, sizeof(void*) * l->capacity * 2);
            l->capacity *= 2;
        }
        else
        {
            l->data = (void **) realloc(l->data, sizeof(void*) * l->capacity * i * 2);
            l->capacity = l->capacity * i * 2;
        }
    }

    l->data[i] = data;
    (l->size)++;
}

void pop(ArrayList * l, int i){
    if (l->size == 0)
        return;
    
    if (i < 0)
            i = l->size + i;
    
    
    for (int j = i; j < l->size - 1; j++)
        l->data[j] = l->data[j + 1];
    
    (l->size)--;
}

void* get(ArrayList * l, int i){
    if (i >= l->capacity)
        return NULL;
    else
    {
        if (i < 0)
            i = l->size + i;

        return l->data[i];
    }
}

int get_size(ArrayList * l){
    return l->size;
}


ArrayList* createGraph()
{
    ArrayList* grafo = createList();
    return grafo;
}

void pushGraph(ArrayList* grafo, void *nodo,int pos)
{
    push(grafo, nodo, pos);
}

void *getGraph(ArrayList* grafo, int indice)
{
    return get(grafo, indice);
}

void popGraph(ArrayList* grafo, int index)
{
    if (index == -1)
        return;
    pop(grafo, index);
}
