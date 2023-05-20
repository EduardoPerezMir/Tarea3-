El programa funciona correctamente en su totalidad. Exceptuando casos donde la precedencia de las tareas es compleja. Ejemplo: 1 precedente de 2, 2 precedente de 3: Al hacer que 3 sea precedente de 1, el programa efectivamente lo hace, lo que implica que exista un "bucle de precedencia". Intenté evitar que ocurriera con la función "buscarTareasSiguientes" (función que buscaría todas las tareas siguientes (recorrer el grafo hacia adelante)) y la función "buscarTareasAnteriores" (función que buscaría todas las tareas anteriores (recorrer todo el grafo hacia atrás)), ambas funciones implementadas de forma recursiva. Debe haber un detalle que hace que no funcione correctamente o no cumpla su cometido, de tal forma que, siguiendo el ejemplo, no logre hallar que ya existía una relación de precedencia entre la tarea 1 y la tarea 3. Sin embargo, ambas funciones sí funcionan correctamente para otros casos como: La función 1 siendo precedente de 2, si se pretende hacer que la función 1 sea precedente de 2 nuevamente, el programa alertará de un error debido a que ya existía una relación de precedencia entre ambas funciones.

Herramientas utilizadas para realizar la tarea: Replit y Github.

Autor: Eduardo Pérez

Coevaluación: No aplica (se realizó el trabajo individualmente).

Autoevaluación:
Participación: 20
Responsabilidad: 20
Comunicación: No aplica.
Calidad de trabajo: 20
Trabajo en equipo: No aplica.

Aspectos positivos: Mentalidad positiva y compromiso permanente con el éxito del trabajo.
Aspectos a mejorar: Algoritmos aún mejorables en eficiencia.
