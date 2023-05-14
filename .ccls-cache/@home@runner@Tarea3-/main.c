#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h"

#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"
#define MAXCHAR 20

typedef struct{
    char nombre[MAXCHAR + 1];
    int prioridad;
    ArrayList *siguiente;
    ArrayList *anterior;
} tipoTarea;

void agregarTarea(HashMap* tareas)
{
    if (tareas->size == tareas->capacity)
        enlarge(tareas);
    
    tipoTarea* nuevaTarea = NULL;
    
    nuevaTarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    printf("Ingrese el nombre de la tarea.\n");
    scanf("%20[^\n]s", nuevaTarea->nombre);
    while (getchar() != '\n');
    
    printf("Ingrese la prioridad de la tarea.\n");
    scanf("%d", &(nuevaTarea->prioridad));
    while (getchar() != '\n');
    nuevaTarea->siguiente = NULL;
    nuevaTarea->anterior = NULL;
    
    pushGraph(tareas, nuevaTarea->nombre, nuevaTarea->prioridad, nuevaTarea);
}

tipoTarea* buscarTareasSiguientes(tipoTarea* tareaParaRecorrer, tipoTarea* tareaBuscada)
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeSig = get_size(tareaParaRecorrer->siguiente);
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tareaParaRecorrer->siguiente->data[i];
        if (strcmp(tareaAux->nombre, tareaBuscada->nombre) == 0)
        {
            return tareaAux;
        }
        
    }
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tareaParaRecorrer->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            buscarTareasSiguientes(tareaAux, tareaBuscada);
    }
    return NULL;
}


void agregarPrecedencia(HashMap* tareas)
{
    tipoTarea* tareaAux = NULL, *tareaAux1 = NULL, *tareaAux2 = NULL;
    trio *trioAux1 = NULL, *trioAux2 = NULL;
    
    char tarea1[MAXCHAR + 1], tarea2[MAXCHAR +1];
    printf("Ingrese el nombre de la tarea 1.\n");
    scanf("%20[^\n]s", tarea1);
    while (getchar() != '\n');

    printf("Ingrese el nombre de la tarea 2.\n");
    scanf("%20[^\n]s", tarea2);
    while (getchar() != '\n');
    int indexT1 = -1, indexT2 = -1;
    trioAux1 = searchGraph(tareas, tarea1);
    trioAux2 = searchGraph(tareas, tarea2);
    
    if (trioAux1 == NULL || trioAux2 == NULL)
    {
        printf("Al menos una de las tareas ingresadas no existe en el sistema\n");
        return;
    }
    
    if (trioAux1->esta == 0)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        trioAux = firstGraph(listaTareas);
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL && buscarTareasSiguientes(tareaAux, tareaAux1) != NULL)
            tareaAux1 = buscarTareasSiguientes(tareaAux, tareaAux1);
        else
        {
            for (int i = 1; i < tareaAux->siguiente->size; i++)
            {
                trioAux = nextGraph(listaTareas);
                tareaAux = trioAux->value;
                if (buscarTareasSiguientes(tareaAux, tareaAux1) != NULL)
                    tareaAux1 = buscarTareasSiguientes(tareaAux, tareaAux1);
            }    
        }
    }
    else
    {
        tareaAux1 = trioAux1->value;
    }

    if (trioAux2->esta == 0)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        trioAux = firstGraph(listaTareas);
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL && buscarTareasSiguientes(tareaAux, tareaAux2) != NULL)
            tareaAux2 = buscarTareasSiguientes(tareaAux, tareaAux2);
        else
        {
            for (int i = 1; i < tareaAux->siguiente->size; i++)
            {
                trioAux = nextGraph(listaTareas);
                tareaAux = trioAux->value;
                if (buscarTareasSiguientes(tareaAux, tareaAux2) != NULL)
                    tareaAux2 = buscarTareasSiguientes(tareaAux, tareaAux2);
            }    
        }
    }
    else
    {
        tareaAux2 = trioAux2->value;
    }
    
    if (tareaAux1 == NULL || tareaAux2 == NULL)
    {
        printf("Al menos una de las tareas ingresadas no existe en el sistema\n");
        return;
    }
    
    if (tareaAux1->siguiente == NULL)
        tareaAux1->siguiente = createList();
    push(tareaAux1->siguiente, tareaAux2, tareaAux1->siguiente->size);
    if (tareaAux2->anterior == NULL)
        tareaAux2->anterior = createList();
    push(tareaAux2->anterior, tareaAux1, tareaAux2->anterior->size);
    
    eraseGraph(tareas, tarea2);
}

void mostrarTareasSiguientes(tipoTarea* tarea)
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeSig = get_size(tarea->siguiente);
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        
        printf("Tarea: %s. Prioridad: %d. Tareas Precedentes: ", tareaAux->nombre, tareaAux->prioridad);
        int sizeAnt = get_size(tareaAux->anterior);
        
        for (int i = 0; i < sizeAnt - 1; i++)
        {
            tareaAux2 = tareaAux->anterior->data[i];
            printf("%s, ", tareaAux2->nombre);
        }
        
        tareaAux2 = tareaAux->anterior->data[sizeAnt - 1];
        printf("%s.\n", tareaAux2->nombre);
    }
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            mostrarTareasSiguientes(tareaAux);
    }
}

void mostrarTareas(HashMap* tareas)
{
    if (tareas->size == 0)    return;
    ArrayList* listaTareas = listaMapa(tareas);
    
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    trio* trioAux = NULL;
    trioAux = firstGraph(listaTareas);
    tareaAux = trioAux->value;
    printf("Tarea: %s. Prioridad: %d\n", tareaAux->nombre, tareaAux->prioridad);
    
    for (int i = 1; i < tareas->size; i++)
    {
        trioAux = nextGraph(listaTareas);
        tareaAux = trioAux->value;
        printf("Tarea: %s. Prioridad: %d\n", tareaAux->nombre, tareaAux->prioridad);
    }

    trioAux = firstGraph(listaTareas);
    tareaAux = trioAux->value;
    if (tareaAux->siguiente != NULL)
    {
        mostrarTareasSiguientes(tareaAux);
    }
    
    for (int i = 1; i < tareas->size; i++)
    {
        trioAux = nextGraph(listaTareas);
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL)
        {
            mostrarTareasSiguientes(tareaAux);
        }        
    }
    
}

int main(void){
   HashMap* tareas = createGraph();
    
    
    int opcionMenu = -1;
    
    printf("Bienvenido a la aplicación de organización de tareas.\n");
        
    while (opcionMenu != 0){
        puts(barrita);
        printf("Elija una opción del menú.\n");
        puts(barrita);
        printf("1. Agregar tarea.\n");
        printf("2. Establecer precedencia entre tareas.\n");
        printf("3. Mostrar tareas por hacer\n");
        printf("4. Marcar tarea como completada \n");
        printf("0.- Salir de la aplicación para organizar tareas.\n");
        printf("Indique la opcion: \n");
        scanf("%d", &opcionMenu);
        while(getchar() != '\n');
        switch(opcionMenu){
            case 1:
                {
                    agregarTarea(tareas);
                    break;
                } 
            case 2:
                {
                    agregarPrecedencia(tareas);
                    break;
                }
            case 3: 
                {
                    mostrarTareas(tareas);
                    break;
                }
           /* case 4: 
                {
                    
                    break;
                }*/
            case 0: 
            {
                printf("Has salido del programa.");
                break;
            }
            default: 
                {
                    printf("No ingreso opción válida.");
                    break;
                }
        }
    }
    return 0;
}
