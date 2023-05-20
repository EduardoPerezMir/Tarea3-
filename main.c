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
    bool fueMostrada; // Variable que ayuda para la opción de mostrar las tareas. 
    bool estaEnMapa; // Variable que ayuda para la opción de eliminar tarea.
    ArrayList *siguiente;
    ArrayList *anterior;
    // Se implementan dos listas de adyacencia.
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
    nuevaTarea->fueMostrada = false;
    nuevaTarea->estaEnMapa = true;
    
    pushGraph(tareas, nuevaTarea->nombre, nuevaTarea->prioridad, nuevaTarea);
}

// La función 'buscarTareasSiguientes' buscaría todas las tareas siguientes (recorre grafo hacia todas las listas de adyacencia 'siguientes').

tipoTarea* buscarTareasSiguientes(tipoTarea* tareaParaRecorrer, char* tareaBuscada)
{
    if (tareaParaRecorrer->siguiente == NULL) return NULL;

    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeSig = get_size(tareaParaRecorrer->siguiente);

    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tareaParaRecorrer->siguiente->data[i];
        if (strcmp(tareaAux->nombre, tareaBuscada) == 0)
        {
            return tareaAux;
        }
        tareaAux = tareaParaRecorrer->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            return buscarTareasSiguientes(tareaAux, tareaBuscada);
    }
    return NULL;
}

// La función 'buscarTareasAnteriores' buscaría todas las tareas anteriores (recorre grafo hacia todas las listas de adyacencia 'anteriores').

tipoTarea* buscarTareasAnteriores(tipoTarea* tareaParaRecorrer, char* tareaBuscada)
{
    if (tareaParaRecorrer->anterior == NULL) return NULL;
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeAnt = get_size(tareaParaRecorrer->anterior);

    for (int i = 0; i < sizeAnt; i++)
    {
        tareaAux = tareaParaRecorrer->anterior->data[i];
        if (strcmp(tareaAux->nombre, tareaBuscada) == 0)
        {
            return tareaAux;
        }
    }
    
    for (int i = 0; i < sizeAnt; i++)
    {
        tareaAux = tareaParaRecorrer->anterior->data[i];
        if (tareaAux->anterior != NULL)
            return buscarTareasSiguientes(tareaAux, tareaBuscada);
    }
    
    return NULL;
}


void agregarPrecedencia(HashMap* tareas)
{
    if (tareas->size == 0)
    {
        printf("No existen registros en el sistema.\n");
        return;
    }
    
    tipoTarea* tareaAux = NULL, *tareaAux1 = NULL, *tareaAux2 = NULL;
    trio *trioAux1 = NULL, *trioAux2 = NULL;
    bool noSeraCiclo = true;

    char tarea1[MAXCHAR + 1], tarea2[MAXCHAR +1];
    printf("Ingrese el nombre de la tarea 1.\n");
    scanf("%20[^\n]s", tarea1);
    while (getchar() != '\n');

    printf("Ingrese el nombre de la tarea 2.\n");
    scanf("%20[^\n]s", tarea2);
    while (getchar() != '\n');
    int indexT1 = -1, indexT2 = -1;

    if (strcmp(tarea1, tarea2) == 0)
    {
        printf("Error. No se puede establecer esta relación de precedencia.\n");
        return;
    }

    if (searchGraph(tareas, tarea1) == NULL)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        trioAux = firstGraph(listaTareas);
        tareaAux = trioAux->value;
        
        if (buscarTareasSiguientes(tareaAux, tarea1) != NULL)
        {
            tareaAux1 = buscarTareasSiguientes(tareaAux, tarea1);
            if (buscarTareasSiguientes(tareaAux1, tarea2) != NULL || buscarTareasAnteriores(tareaAux1, tarea2) != NULL)
            {
                printf("Error. No se puede establecer esta relación de precedencia.\n");
                return;
            }
        }
        else
        {
            for (int i = 1; i < listaTareas->size; i++)
            {
                trioAux = nextGraph(listaTareas);
                tareaAux = trioAux->value;
                if (buscarTareasSiguientes(tareaAux, tarea1) != NULL)
                {
                    tareaAux1 = buscarTareasSiguientes(tareaAux, tarea1);
                    if (buscarTareasSiguientes(tareaAux1, tarea2) != NULL || buscarTareasAnteriores(tareaAux1, tarea2) != NULL)
                    {
                        printf("Error. No se puede establecer esta relación de precedencia.\n");
                        return;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        trioAux1 = searchGraph(tareas, tarea1);
        tareaAux1 = trioAux1->value;
    }
    
    if (searchGraph(tareas, tarea2) == NULL)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        trioAux = firstGraph(listaTareas);
        tareaAux = trioAux->value;
        
        if (buscarTareasSiguientes(tareaAux, tarea2) != NULL)
        {
            tareaAux2 = buscarTareasSiguientes(tareaAux, tarea2);
            
            if (buscarTareasSiguientes(tareaAux2, tarea1) != NULL || buscarTareasAnteriores(tareaAux2, tarea1) != NULL)
            {
                printf("Error. No se puede establecer esta relación de precedencia.\n");
                return;
            }
        }
        else
        {
            for (int i = 1; i < listaTareas->size; i++)
            {
                trioAux = nextGraph(listaTareas);
                tareaAux = trioAux->value;
                
                if (buscarTareasSiguientes(tareaAux, tarea2) != NULL)
                {
                    tareaAux2 = buscarTareasSiguientes(tareaAux, tarea2);
                    if (buscarTareasSiguientes(tareaAux2, tarea1) != NULL || buscarTareasAnteriores(tareaAux2, tarea1) != NULL)
                    {
                        printf("Error. No se puede establecer esta relación de precedencia.\n");
                        return;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        trioAux2 = searchGraph(tareas, tarea2);
        tareaAux2 = trioAux2->value;
    }
    
    if (tareaAux1 == NULL || tareaAux2 == NULL)
    {
        printf("Error: Al menos una de las tareas ingresadas no existe en el sistema\n");
        return;
    }
    
    if (tareaAux1->siguiente == NULL)
        tareaAux1->siguiente = createList();
    push(tareaAux1->siguiente, tareaAux2, tareaAux1->siguiente->size);
    if (tareaAux2->anterior == NULL)
        tareaAux2->anterior = createList();
    push(tareaAux2->anterior, tareaAux1, tareaAux2->anterior->size);
    
    if (tareaAux2->estaEnMapa != false)
    {
        eraseGraph(tareas, tarea2);
        tareaAux2->estaEnMapa = false;
    }
    
    printf("La tarea %s es precedente a la tarea %s.\n", tarea1, tarea2);
}

void mostrarTareasLista(ArrayList* lista)
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    
    for (int i = 0; i < lista->size; i++)
    {
        tareaAux = lista->data[i];
        printf("Tarea: %s. Prioridad: %d. Tareas Precedentes: ", tareaAux->nombre, tareaAux->prioridad);
        int sizeAnt = get_size(tareaAux->anterior);
        
        for (int i = 0; i < sizeAnt - 1; i++)
        {
            tareaAux2 = tareaAux->anterior->data[i];
            printf("%s, ", tareaAux2->nombre);
        }
        
        tareaAux2 = tareaAux->anterior->data[sizeAnt - 1];
        printf("%s.\n", tareaAux2->nombre);
        tareaAux->fueMostrada = true;
    }
}

void ordenarLista(ArrayList* listaOrdenadaElem)
{
    tipoTarea *temp = (tipoTarea*) malloc(sizeof(tipoTarea));
    tipoTarea *aux1 = (tipoTarea*) malloc(sizeof(tipoTarea));
    tipoTarea *aux2 = (tipoTarea*) malloc(sizeof(tipoTarea));
    
    for (int i = 1 ; i < listaOrdenadaElem->size; i++)
    {
       for (int j = 0; j < listaOrdenadaElem->size - i; j++)
       {
           aux1 = listaOrdenadaElem->data[j];
           aux2 = listaOrdenadaElem->data[j+1];
          if (aux1->prioridad > aux2->prioridad)
          {
            temp = listaOrdenadaElem->data[j];
            listaOrdenadaElem->data[j] = listaOrdenadaElem->data[j+1];
            listaOrdenadaElem->data[j+1] = temp;
          }
       }
    }
    mostrarTareasLista(listaOrdenadaElem);
}

void armarLista(tipoTarea* tarea)
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeSig = get_size(tarea->siguiente);
    ArrayList* listaAux = createList();
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        if (tareaAux->fueMostrada == false)
        {
            push(listaAux, tareaAux, listaAux->size);
        }
        
        tareaAux->fueMostrada = true;
    }
    
    ordenarLista(listaAux);
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            armarLista(tareaAux);
    }
}

void desmarcarTareas(tipoTarea* tarea)
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    int sizeSig = get_size(tarea->siguiente);
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        tareaAux->fueMostrada = false;
    }
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            desmarcarTareas(tareaAux);
    }
}

void mostrarTareas(HashMap* tareas)
{
    if (tareas->size == 0)    
    {
        printf("No hay tareas en el sistema.\n");
        return;
    }
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
    ArrayList* listaAuxiliar = createList();
    
    if (tareaAux->siguiente != NULL)
    {
        armarLista(tareaAux);
    }
    
    for (int i = 1; i < tareas->size; i++)
    {
        trioAux = nextGraph(listaTareas);
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL)
        {
            armarLista(tareaAux);
        }
    }
    
    trioAux = firstGraph(listaTareas);
    tareaAux = trioAux->value;
    if (tareaAux->siguiente != NULL)
    {
        desmarcarTareas(tareaAux);
    }

    
    for (int i = 1; i < tareas->size; i++)
    {
        trioAux = nextGraph(listaTareas);
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL)
        {
            desmarcarTareas(tareaAux);
        }
    }
}

void desvincularTareasSiguientesMapa(ArrayList* lista, HashMap* tareas, char marcada[])
{
    tipoTarea* tareaAux = NULL;
    
    for (int i = 0; i < lista->size; i++)
    {
        tareaAux = lista->data[i];
        if (tareaAux->anterior->size == 1)
        {
            pop(tareaAux->anterior, 0);
            tareaAux->estaEnMapa = true;
            pushGraph(tareas, tareaAux->nombre, tareaAux->prioridad, tareaAux);
        }
        else
        {
            char nombreAux[MAXCHAR + 1];
            for (int j = 0; j < tareaAux->anterior->size; j++)
            {
                strcpy(nombreAux, tareaAux->anterior->data[j]);
                if (strcmp(nombreAux, marcada) == 0)
                {
                    pop(tareaAux->anterior, j);
                    break;
                }
            }
        }
    }
}

void desvincularTareasSiguientesLista(ArrayList* lista1, ArrayList* lista2, HashMap* tareas, char marcada[])
{
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    tipoTarea* ptrTareaAux = NULL;
    
    for (int i = 0; i < lista1->size; i++)
    {
        ptrTareaAux = lista1->data[i];
        for (int j = 0; j < lista2->size; j++)
        {
            tareaAux = lista2->data[j];
            push(tareaAux->siguiente, ptrTareaAux, tareaAux->siguiente->size);
            push(ptrTareaAux->anterior, tareaAux, ptrTareaAux->anterior->size);
        }
    }
    
    for (int i = 0; i < lista1->size; i++)
    {
        ptrTareaAux = lista1->data[i];
        for (int j = 0; j < ptrTareaAux->anterior->size; j++)
        {
            tareaAux2 = ptrTareaAux->anterior->data[j];
            if (strcmp(tareaAux2->nombre, marcada) == 0)
            {
                pop(ptrTareaAux->anterior, j);
                break;
            }
        }
    }
    
}

void marcarTarea(HashMap* tareas)
{
    if (tareas->size == 0)    return;
    
    tipoTarea* tareaMarcadaAux;
    trio* trioAux = NULL;
    tipoTarea* tareaAux = NULL;   

    char tareaMarcada[MAXCHAR + 1];
    printf("Ingrese el nombre de la tarea a marcar como completada.\n");
    scanf("%20[^\n]s", tareaMarcada);
    while (getchar() != '\n');

    if (searchGraph(tareas, tareaMarcada) == NULL)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        
        trioAux = firstGraph(listaTareas);
        tareaAux = trioAux->value;
        
        if (buscarTareasSiguientes(tareaAux, tareaMarcada) != NULL)
        {
            tareaMarcadaAux = buscarTareasSiguientes(tareaAux, tareaMarcada);
        }

        else
        {
            for (int i = 1; i < listaTareas->size; i++)
            {
                trioAux = nextGraph(listaTareas);
                tareaAux = trioAux->value;
                if (buscarTareasSiguientes(tareaAux, tareaMarcada) != NULL)
                {
                    tareaMarcadaAux = buscarTareasSiguientes(tareaAux, tareaMarcada);
                    break;
                }
            }
        }
    }
    else
    {
        trioAux = searchGraph(tareas, tareaMarcada);
        tareaMarcadaAux = trioAux->value;
        if (tareaMarcadaAux->siguiente == NULL)
        {
            eraseMap(tareas, tareaMarcada);
            return;
        }
    }
    
    if (tareaMarcadaAux == NULL)
    {
        printf("Error: La tarea señalada no existe en el sistema.\n");
        return;
    }

    tipoTarea* tareaAux2 = NULL;
    tipoTarea* tareaAux3 = NULL;
    char respuesta;
    if (tareaMarcadaAux->siguiente != NULL || tareaMarcadaAux->anterior != NULL)
    {
        
        printf("¿Está seguro de eliminar esta tarea con relaciones de precedencia? s/n\n");
        scanf("%c", &respuesta);
    }
    if (respuesta == 's')
    {
        if (tareaMarcadaAux->estaEnMapa == true)
        {
    
                desvincularTareasSiguientesMapa(tareaMarcadaAux->siguiente, tareas, tareaMarcadaAux->nombre);
                eraseMap(tareas, tareaMarcadaAux);
        }
        else
        {
            if (tareaMarcadaAux->siguiente != NULL)
            {
                desvincularTareasSiguientesLista(tareaMarcadaAux->siguiente, tareaMarcadaAux->anterior, tareas, tareaMarcadaAux->nombre);
            }
            
            for (int i = 0; i < tareaMarcadaAux->anterior->size; i++)
            {
                tareaAux2 = tareaMarcadaAux->anterior->data[i];
    
                for (int j = 0; j < tareaAux2->siguiente->size; j++)
                {
                    tareaAux3 = tareaAux2->siguiente->data[j];
                    if (strcmp(tareaMarcada, tareaAux3->nombre) == 0)
                    {
                        pop(tareaAux2->siguiente, j);
                        break;
                    }
                }
            }
        }
        printf("La tarea %s ha sido marcada como completa.", tareaMarcada);
    }
    else if (respuesta == 'n')
    {
        printf("No se ha eliminado la tarea.");
    }
    else
    {
        printf("No se ingresó una opción válida.");
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
        printf("3. Mostrar tareas por hacer.\n");
        printf("4. Marcar tarea como completada.\n");
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
            case 4: 
                {
                    marcarTarea(tareas);
                    break;
                }
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
