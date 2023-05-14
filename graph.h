#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef Grafo_h
#define Grafo_h

#define MAXCHAR 20
#define INITIALCAPAC 20

typedef struct ArrayList ArrayList;

struct ArrayList{
    void **data;
    int capacity;
    int size;
    int current;
};


ArrayList *createList(void);

void push(ArrayList * l, void* data, int i);
void pop(ArrayList * l, int i);
void* get(ArrayList * l, int i);
int get_size(ArrayList * l);


typedef struct HashMap HashMap;

typedef struct trio{
    char *key1;
    int key2;
    void * value;
    int esta;
} trio;

struct HashMap{
    trio **buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};


HashMap * createMap(int capacity);
void insertMap(HashMap* table, void* key1, int key2, void* value);
void eraseMap(HashMap* table, void* key1);
trio * searchMap(HashMap* table, void* key1);
ArrayList* listaMapa(HashMap* map);
trio * firstMap(ArrayList* lista);
trio * nextMap(ArrayList* lista);
void enlarge(HashMap* map);



HashMap *createGraph();
void pushGraph(HashMap* grafo, void* clave, int clave2, void* value);
trio* searchGraph(HashMap* grafo, void* clave);
void eraseGraph(HashMap* grafo, void* clave);
trio* firstGraph(ArrayList* listaGrafo);
trio* nextGraph(ArrayList* listaGrafo);

#endif
