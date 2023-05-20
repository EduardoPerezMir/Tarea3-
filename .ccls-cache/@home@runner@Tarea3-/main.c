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
    
    insertMap(tareas, nuevaTarea->nombre, nuevaTarea->prioridad, nuevaTarea);
}

// La función 'buscarTareasSiguientes' busca todas las tareas siguientes (recorre grafo hacia todas las listas de adyacencia 'siguientes').

tipoTarea* buscarTareasSiguientes(tipoTarea* tareaParaRecorrer, char tareaBuscada[])
{
    if (tareaParaRecorrer->siguiente == NULL) return NULL;

    tipoTarea* tareaAux = NULL;

    for (int i = 0; i < tareaParaRecorrer->siguiente->size; i++)
    {
        tareaAux = tareaParaRecorrer->siguiente->data[i];
        if (strcmp(tareaAux->nombre, tareaBuscada) == 0)
            return tareaAux;

        if (tareaAux->siguiente != NULL && buscarTareasSiguientes(tareaAux, tareaBuscada) != NULL)
            return buscarTareasSiguientes(tareaAux, tareaBuscada);
    }
    
    return NULL;
}

// La función 'buscarTareasAnteriores' busca todas las tareas anteriores (recorre grafo hacia todas las listas de adyacencia 'anteriores').

tipoTarea* buscarTareasAnteriores(tipoTarea* tareaParaRecorrer, char tareaBuscada[])
{
    if (tareaParaRecorrer->anterior == NULL) return NULL;
    tipoTarea* tareaAux = NULL;

    for (int i = 0; i < tareaParaRecorrer->anterior->size; i++)
    {
        tareaAux = tareaParaRecorrer->anterior->data[i];
        if (strcmp(tareaAux->nombre, tareaBuscada) == 0)
            return tareaAux;
        
        if (tareaAux->anterior != NULL && buscarTareasAnteriores(tareaAux, tareaBuscada) != NULL)
            return buscarTareasAnteriores(tareaAux, tareaBuscada);
    }
    
    return NULL;
}

//La función 'agregarPrecedencia' establece precedencia entre tareas, considerando que no puede haber precedencia entre tareas si no se encuentran en el mismo nivel o en niveles adyacentes (para verificar eso, se llama a las dos funciones anteriores).


void agregarPrecedencia(HashMap* tareas)
{
    if (tareas->size == 0)
    {
        printf("No existen registros en el sistema.\n");
        return;
    }
    
    tipoTarea *tareaAux1 = NULL, *tareaAux2 = NULL;
    trio *trioAux1 = NULL, *trioAux2 = NULL;

    char tarea1[MAXCHAR + 1], tarea2[MAXCHAR + 1];
    printf("Ingrese el nombre de la tarea 1.\n");
    scanf("%20[^\n]s", tarea1);
    while (getchar() != '\n');

    printf("Ingrese el nombre de la tarea 2.\n");
    scanf("%20[^\n]s", tarea2);
    while (getchar() != '\n');

    if (strcmp(tarea1, tarea2) == 0)
    {
        printf("Error. No se puede establecer esta relación de precedencia.\n");
        return;
    }

    if (searchMap(tareas, tarea1) == NULL) // Si la tarea 1 no está en el mapa.
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        for (int i = 0; i < listaTareas->size; i++)
        {
            trioAux = listaTareas->data[i]; // Se busca en todas las listas adyacentes a todos los elementos del mapa.
            tareaAux = trioAux->value;
            if (buscarTareasSiguientes(tareaAux, tarea1) != NULL)
            {
                tareaAux1 = buscarTareasSiguientes(tareaAux, tarea1);
                if (buscarTareasSiguientes(tareaAux1, tarea2) != NULL || buscarTareasAnteriores(tareaAux1, tarea2) != NULL) // Se verifica que no exista una relación de precedencia previa, de forma que solamente se puedan dar relaciones de precedencia válidas.
                {
                    printf("Error. No se puede establecer esta relación de precedencia.\n");
                    return;
                }
                break;
            }
        }
    }
    else
    {
        trioAux1 = searchMap(tareas, tarea1); // Si la tarea 1 está en el mapa, simplemente se le asigna esa referencia a trioAux1, luego el valor es asignado a tareaAux1 (lo mismo aplica para tarea2 en las siguientes líneas de código).
        tareaAux1 = trioAux1->value;
    }
    
    if (searchMap(tareas, tarea2) == NULL)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        tipoTarea* tareaAux = NULL;
        trio* trioAux = NULL;
        
        for (int i = 0; i < listaTareas->size; i++)
        {
            trioAux = listaTareas->data[i];
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
    else
    {
        trioAux2 = searchMap(tareas, tarea2);
        tareaAux2 = trioAux2->value;
    }
    
    if (tareaAux1 == NULL || tareaAux2 == NULL)
    {
        printf("Error: Al menos una de las tareas ingresadas no existe en el sistema\n");
        return;
    }
    
    if (tareaAux1->siguiente == NULL)
        tareaAux1->siguiente = createList();
    push(tareaAux1->siguiente, tareaAux2, tareaAux1->siguiente->size); // Se inserta la tarea 2 en la lista de tareas siguientes a la tarea 1.
    if (tareaAux2->anterior == NULL)
        tareaAux2->anterior = createList();
    push(tareaAux2->anterior, tareaAux1, tareaAux2->anterior->size); // Se inserta la tarea 1 en la lista de tareas anteriores a la tarea 2.
    
    if (tareaAux2->estaEnMapa != false)
    {
        eraseMap(tareas, tarea2); // Si está en el mapa, se elimina del mapa.
        tareaAux2->estaEnMapa = false;
    }
    
    printf("La tarea %s es precedente a la tarea %s.\n", tarea1, tarea2);
}

// En la función 'mostrarTareasLista' se muestra la lista de tareas siguientes, previamente ordenadas por prioridad.

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

// Se aplica ordenamiento búrbuja para luego mostrar la lista.

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

// La función 'armarLista' arma sub listas del grafo, para ir mostrándolas posteriormente de forma ordenada por prioridad.

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
        
        tareaAux->fueMostrada = true; // Para evitar mostrar de forma repetida un elemento del grafo, se usa ese valor booleano auxiliar.
    }
    
    ordenarLista(listaAux);
    
    for (int i = 0; i < sizeSig; i++)
    {
        tareaAux = tarea->siguiente->data[i];
        if (tareaAux->siguiente != NULL)
            armarLista(tareaAux);
    }
}

// Para luego mostrar nuevamente, se 'desmarca el grafo', es decir, se re-inicializa el valor booleano auxliar como falso, para así mostrar nuevamente el grafo, en caso de ser pedido.

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
    if (tareas->size == 0)    // Caso límite.
    {
        printf("No hay tareas en el sistema.\n"); 
        return;
    }
    
    ArrayList* listaTareas = listaMapa(tareas); // la función listaMapa retorna una lista ordenada por prioridad, dando como parametro el mapa de tareas.
    
    tipoTarea* tareaAux = NULL, *tareaAux2 = NULL;
    trio* trioAux = NULL;
    
    for (int i = 0; i < tareas->size; i++)
    {
        trioAux = listaTareas->data[i]; // Se recorre el mapa.
        tareaAux = trioAux->value;
        printf("Tarea: %s. Prioridad: %d\n", tareaAux->nombre, tareaAux->prioridad);
    }
    
    for (int i = 0; i < tareas->size; i++)
    {
        trioAux = listaTareas->data[i];
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL)
        {
            armarLista(tareaAux); // Se arman todas las sub-listas de todas las tareas precedentes a las tareas precedentes a las tareas del mapa.
        }
    }

    
    for (int i = 0; i < tareas->size; i++)
    {
        trioAux = listaTareas->data[i];
        tareaAux = trioAux->value;
        if (tareaAux->siguiente != NULL)
        {
            desmarcarTareas(tareaAux); // Se 're-inicializa el grafo' para ser mostrado nuevamente.
        }
    }
}

// La función 'desvincularTareasSiguientesMapa' se encarga de anular todas las conexiones de punteros entre el elemento del mapa a eliminar y sus elementos de precedencia.

void desvincularTareasSiguientesMapa(ArrayList* lista, HashMap* tareas, char marcada[])
{
    tipoTarea* tareaAux = NULL;
    
    for (int i = 0; i < lista->size; i++)
    {
        tareaAux = lista->data[i];
        if (tareaAux->anterior->size == 1) // Si el elemento a eliminar era el único anterior, entonces todos los elementos siguientes al elemento a eliminar se insertan en el mapa.
        {
            pop(tareaAux->anterior, 0);
            tareaAux->estaEnMapa = true;
            insertMap(tareas, tareaAux->nombre, tareaAux->prioridad, tareaAux);
        }
        else
        { // En caso contrario, simplemente se anula esa conexión de punteros.
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

// La función 'desvincularTareasSiguientesLista' se encarga de anular todas las conexiones de punteros entre un elemento a eliminar del grafo (que no está en el mapa, sino en una lista de adyacencia) y sus relaciones de precedencia. De tal forma, que se reorganizan los datos.

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
            push(tareaAux->siguiente, ptrTareaAux, tareaAux->siguiente->size); // Al borrar un elemento 'x', se hace la conexión entre los elementos anteriores a x y los siguientes a x. Para seguir la lógica de relaciones de precedencia.
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

// La función 'marcarTarea' se encarga de realizar la opción 4 del menú, llamando a otras funciones para realizar su cometido.

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

    if (searchMap(tareas, tareaMarcada) == NULL)
    {
        ArrayList* listaTareas = listaMapa(tareas);
        
        for (int i = 0; i < listaTareas->size; i++)
        {
            trioAux = listaTareas->data[i];
            tareaAux = trioAux->value;
            if (buscarTareasSiguientes(tareaAux, tareaMarcada) != NULL)
            {
                tareaMarcadaAux = buscarTareasSiguientes(tareaAux, tareaMarcada);
                break;
            }
        }
    }
    else
    {
        trioAux = searchMap(tareas, tareaMarcada);
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
        
        printf("¿Está seguro de eliminar esta tarea con relaciones de precedencia? s/n\n"); // En caso de que el elemento que se desea eliminar tenga relaciones de precedencia, se preguntará al usuario si está seguro de eliminar el elemento. Tal y como fue indicado en las instrucciones.
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
   HashMap* tareas = createMap();
    
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
