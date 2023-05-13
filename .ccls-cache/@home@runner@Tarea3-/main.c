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

void agregarTarea(ArrayList* tareas)
{
    tipoTarea* nuevaTarea = NULL;
    char nombreAux[MAXCHAR + 1];
    int prioridadAux;
    
    nuevaTarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    printf("Ingrese el nombre de la tarea.\n");
    scanf("%20[^\n]s", nuevaTarea->nombre);
    while (getchar() != '\n');
    
    printf("Ingrese la prioridad de la tarea.\n");
    scanf("%d", &(nuevaTarea->prioridad));
    while (getchar() != '\n');
    nuevaTarea->siguiente = NULL;
    nuevaTarea->anterior = NULL;
    if (getGraph(tareas, nuevaTarea->prioridad) != NULL)
    {
        printf("Error. No pueden haber dos tareas con la misma prioridad");
        return;
    }
    pushGraph(tareas, nuevaTarea, nuevaTarea->prioridad);
}

void agregarPrecedencia(ArrayList* tareas)
{
    tipoTarea* tareaAux = NULL, *tareaAux1 = NULL, *tareaAux2 = NULL;
    int size = get_size(tareas);
    bool existeT1 = false, existeT2 = false;
    char tarea1[MAXCHAR + 1], tarea2[MAXCHAR +1];
    printf("Ingrese el nombre de la tarea 1.\n");
    scanf("%20[^\n]s", tarea1);
    while (getchar() != '\n');

    printf("Ingrese el nombre de la tarea 2.\n");
    scanf("%20[^\n]s", tarea2);
    while (getchar() != '\n');
    int indexT1 = -1, indexT2 = -1;
    
    for (int i = 0; i < tareas->capacity; i++)
    {
        tareaAux = tareas->data[i];
        if (tareaAux != NULL)
        {
            if (strcmp(tareaAux->nombre, tarea1) == 0)
            {
                existeT1 = true;
                indexT1 = i;
                size--;
                if (size == 0)    break;
            }
            if (strcmp(tareaAux->nombre, tarea2) == 0)
            {
                existeT1 = true;
                indexT2 = i;
                size--;
                if (size == 0)    break;
            }
        }
        if (existeT1 && existeT2)
            break;
    }
    tareaAux1 = tareas->data[indexT1];
    tareaAux2 = tareas->data[indexT2];
    if (tareaAux1->siguiente == NULL)
        tareaAux1->siguiente = createList();
    push(tareaAux1->siguiente, tareaAux2, tareaAux1->siguiente->size);
    if (tareaAux2->anterior == NULL)
        tareaAux2->anterior = createList();
    push(tareaAux2->anterior, tareaAux1, tareaAux2->anterior->size);
}

void mostrarTareas(ArrayList* tareas)
{
    if (tareas->size == 0)    return;
    
    tipoTarea* tareaAux = NULL;
    int size = get_size(tareas);
    
    for (int i = 0; i < tareas->capacity; i++)
    {
        tareaAux = tareas->data[i];
        if (tareaAux != NULL && tareaAux->anterior == NULL)
        {
            printf("%s, %d\n", tareaAux->nombre, tareaAux->prioridad);
            size--;
            if (size == 0)    
                return;
        }
    }

    size = get_size(tareas);
    tipoTarea *tareaAux2 = NULL;
    
    for (int i = 0; i < tareas->capacity; i++)
    {
        tareaAux = tareas->data[i];
        if (tareaAux != NULL && tareaAux->anterior != NULL)
        {
            printf("%s, %d - Precedente: ", tareaAux->nombre, tareaAux->prioridad);
            for (int j = 0; j < tareaAux->anterior->size; j++)
            {
                tareaAux2 = tareaAux->anterior->data[j];
                printf(", %s", tareaAux2->nombre);
            }
            printf("\n");
            size--;
            if (size == 0)    break;
        }
    }
}

int main(void){
    ArrayList* tareas = createList();
    
    
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
