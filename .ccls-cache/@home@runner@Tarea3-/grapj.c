#include <stdlib.h>
#include <assert.h>
#include "grafo.h"

ArrayList* createGraph()
{
    ArrayList* grafo = createList();
    return grafo;
}

void pushGraph(ArrayList* grafo, nodoGrafo* nodo)
{
    push(grafo, nodo, nodo->prioridad - 1);

}



