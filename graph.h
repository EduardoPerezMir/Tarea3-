#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef Grafo_h
#define Grafo_h

#define MAXCHAR 20
#define INITIALCAPAC 10 

typedef struct ArrayList ArrayList;

struct ArrayList{
    void **data;
    int capacity;
    int size;
};


ArrayList *createList(void);

void push(ArrayList * l, void* data, int i);
void pop(ArrayList * l, int i);
void* get(ArrayList * l, int i);
int get_size(ArrayList * l);



ArrayList *createGraph();
void pushGraph(ArrayList* grafo, void *nodo,int pos);
void* getGraph(ArrayList* grafo, int indice);
void popGraph(ArrayList* grafo, int index);

#endif