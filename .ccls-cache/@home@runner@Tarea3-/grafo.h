#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

#ifndef Grafo_h
#define Grafo_h

#define MAXCHAR 20
#define INITIALCAPAC 10 

typedef struct nodoGrafo nodoGrafo;

struct nodoGrafo{
    char nombre;//nombre del vertice o nodo
    int prioridad;
    ArrayList *siguiente;
    ArrayList *anterior;//puntero hacia la primera arista del nodo
};

ArrayList *createGraph();
void pushGraph(ArrayList* grafo, nodoGrafo* nodo);
void searchGraph(ArrayList* grafo, nodoGrafo* nodo);
void popGraph(ArrayList* grafo, nodoGrafo* nodo);

#endif