#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"
#define MAXCHAR 20

typedef struct{
    char nombre[MAXCHAR + 1];
    int prioridad;
} tipoTarea;

void agregarTarea(Heap* monticulo)
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
    
    heap_push(monticulo, nuevaTarea->nombre, nuevaTarea->prioridad);
}




int main(void){
    Heap* monticulo = createHeap();
    
    
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
                    agregarTarea(monticulo);
                    break;
                } 
            /*case 2:
                {
                    
                    break;
                }
            case 3: 
                {
                    
                    break;
                }
            case 4: 
                {
                    
                    break;
                }*/
            default: 
                {
                    printf("No ingreso opción válida.");
                    break;
                }
        }
    }
    return 0;
}
