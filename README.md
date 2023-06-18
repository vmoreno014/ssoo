# Sistemas Operativos - EHU

## Para compilar
`gcc -o programa main.c -lpthread`

## Para ejecutar
`./programa`

## Explicación
1. Se incluyen los archivos de encabezado necesarios, como `stdio.h`, `stdlib.h` y `pthread.h`. Además, se incluyen los encabezados de "process.h", "priority_queue.h", "scheduler.h" y "process_generator.h". Estos encabezados probablemente contienen las declaraciones de las funciones y estructuras de datos utilizadas en el programa principal.

2. La función `main()` comienza creando tres procesos utilizando la función `createProcess()` del encabezado "process.h". A cada proceso se le asigna un ID, una prioridad y un tiempo de ejecución.

3. Los procesos se almacenan en un arreglo llamado `processes`, y se calcula el número total de procesos.

4. Se inicializa una cola de prioridad utilizando la función `initPriorityQueue()` del encabezado "priority_queue.h". La variable `capacity` especifica el número máximo de procesos que la cola de prioridad puede contener.

5. Se crea una estructura `SchedulerArgs` utilizando asignación de memoria dinámica. Esta estructura contiene los argumentos necesarios para la función `scheduleProcesses()`, que se encarga de programar los procesos. La estructura `SchedulerArgs` se inicializa con el arreglo de procesos, el número de procesos, una cantidad de tiempo para cada rebanada de tiempo (time slice) y una referencia a la cola de prioridad.

6. Se crea un hilo (thread) utilizando `pthread_create()` para ejecutar la función `scheduleProcesses()`. El identificador del hilo se almacena en la variable `schedulerThread`.

7. Se crea otra estructura `ProcessGeneratorArgs` utilizando asignación de memoria dinámica. Esta estructura contiene los argumentos necesarios para la función `processGenerator()`, que se encarga de generar nuevos procesos de forma periódica. La estructura `ProcessGeneratorArgs` se inicializa con la frecuencia de generación de procesos, el arreglo de procesos, el número de procesos, la rebanada de tiempo y referencias al hilo del programador y la cola de prioridad.

8. Se crea otro hilo utilizando `pthread_create()` para ejecutar la función `processGenerator()`. El identificador del hilo se almacena en la variable `generatorThread`.

9. Se utiliza `pthread_join()` para esperar a que el hilo del generador de procesos termine su ejecución.

10. Se realiza una limpieza de memoria liberando los recursos utilizados, incluyendo la destrucción de los procesos, la cola de prioridad y la liberación de las estructuras `SchedulerArgs` y `ProcessGeneratorArgs`.

11. El programa finaliza y devuelve 0 como estado de salida.

Este código crea dos hilos: 
- uno para la generación periódica de procesos
- otro para la programación de los procesos en una cola de prioridad.

El programa simula el proceso de generación y programación de procesos en un entorno concurrente utilizando hilos POSIX.

*Más información en el archivo:* [Memoria.pdf](Memoria.pdf)
