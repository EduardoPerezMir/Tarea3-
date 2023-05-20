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
    if (l->size == l->capacity)
    {
        l->data = (void **) realloc(l->data, sizeof(void*) * l->capacity * 2);
        l->capacity *= 2;
    }

    l->data[i] = data;
    (l->size)++;
}

void pop(ArrayList * l, int i){
    if (l->size == 0)
        return;
    
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

trio * createTrio( char * key1, int key2, void * value) {
    trio * new = (trio *)malloc(sizeof(trio));
    new->key1 = key1;
    new->key2 = key2;
    new->value = value;
    return new;
}

long hash( char * key, int capacity) {
    unsigned int hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

HashMap *createMap(int capacity) {
    HashMap *map = NULL;
    map = (HashMap*) malloc(sizeof(HashMap));
    if (map == NULL)
        return NULL;
    
    map->buckets = (trio**) malloc(sizeof(trio*) * capacity);
    if (map->buckets == NULL)
        return NULL;
    
    for (long i = 0; i < capacity; i++)
        map->buckets[i] = NULL;
    
    map->capacity = capacity;
    map->size = 0;
    return map;
}




void insertMap(HashMap * map, void *key1, int key2 ,void * value) {
    long indice = hash(key1, map->capacity);
    
    while (map->buckets[indice] != NULL)
    {
        indice++;
        if (indice == map->capacity)
            indice = 0;
    }
    
    map->buckets[indice] = (trio*) malloc(sizeof(trio));
    map->buckets[indice]->key1 = key1;
    map->buckets[indice]->key2 = key2;
    map->buckets[indice]->value = value;
    map->size++;
}

void eraseMap(HashMap * map, void* key1) {    
    long indice = hash(key1, map->capacity);
    
    if (map->buckets[indice] == NULL)
        return;
    
    while (strcmp(map->buckets[indice]->key1, key1) != 0)
    {
        indice++;
        if (indice == map->capacity)
            indice = 0;
        
        if (map->buckets[indice] == NULL)
            return;
    }
    
    map->buckets[indice] = NULL;
    map->size--;
}

ArrayList* listaNoOrdenadaMapa(HashMap* map)
{
    ArrayList* lista = createList();
    
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->buckets[i] != NULL)
        {
            push(lista, map->buckets[i], lista->size);
        }
    }
    return lista;
}

void enlarge(HashMap * map) {
    trio** auxBuckets = (trio**) malloc(sizeof(trio*) * map->size);
    
    ArrayList* listaAux = listaNoOrdenadaMapa(map);

    for (long i = 0; i < map->capacity; i++)
    {
        if (map->buckets[i] != NULL)
        {
            eraseMap(map, map->buckets[i]->key1);
        }
    }

    map->buckets = (trio **) realloc(map->buckets, sizeof(trio*) * map->capacity * 2);
    if (map->buckets == NULL)
        return;

    for (long i = map->capacity; i < map->capacity * 2; i++)
    {
        map->buckets[i] = NULL;
    }
    
    map->capacity *= 2;
    
    
    for (long i = 0; i < listaAux->size; i++)
    {
        trio* trioAux = (trio*) malloc(sizeof(trio));
        trioAux = listaAux->data[i];
        insertMap(map, trioAux->key1, trioAux->key2, trioAux->value);
    }
}

trio *searchMap(HashMap * map,  void* key1) {
    long indice = hash(key1, map->capacity);
    
    if (map->buckets[indice] == NULL)
            return NULL;
    
    while (strcmp(map->buckets[indice]->key1, key1) != 0)
    {
        indice++;
        if (indice == map->capacity)
            indice = 0;
        
        if (map->buckets[indice] == NULL)
            return NULL;
    }
    
    return map->buckets[indice];
}

ArrayList* listaMapa(HashMap* map)
{
    ArrayList* listaOrdenadaElem = createList();
    
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->buckets[i] != NULL)
        {
            push(listaOrdenadaElem, map->buckets[i], listaOrdenadaElem->size);
        }
    }
    trio *temp = (trio*) malloc(sizeof(trio));
    trio *aux1 = (trio*) malloc(sizeof(trio));
    trio *aux2 = (trio*) malloc(sizeof(trio));
    
    for (int i = 1 ; i < listaOrdenadaElem->size; i++)
    {
       for (int j = 0; j < listaOrdenadaElem->size - i; j++)
       {
           aux1 = listaOrdenadaElem->data[j];
           aux2 = listaOrdenadaElem->data[j+1];
          if (aux1->key2 > aux2->key2)
          {
            temp = listaOrdenadaElem->data[j];
            listaOrdenadaElem->data[j] = listaOrdenadaElem->data[j+1];
            listaOrdenadaElem->data[j+1] = temp;
          }
       }
    }
    return listaOrdenadaElem;
}

trio* firstMap(ArrayList* lista) {
    lista->current = 0;
    return lista->data[0];
}

trio* nextMap(ArrayList* lista) {
    lista->current++;
    return lista->data[lista->current];
}

HashMap* createGraph()
{
    HashMap* grafo = createMap(INITIALCAPAC);
    return grafo;
}

void pushGraph(HashMap* grafo, void *clave1, int clave2, void* value)
{
    insertMap(grafo, clave1, clave2, value);
}

trio* searchGraph(HashMap* grafo, void* clave)
{
    return searchMap(grafo, clave);
}

void eraseGraph(HashMap* grafo, void *clave)
{
    eraseMap(grafo, clave);
}

trio* firstGraph(ArrayList* lista)
{
    return firstMap(lista);
}

trio* nextGraph(ArrayList* lista)
{
    return nextMap(lista);
}
