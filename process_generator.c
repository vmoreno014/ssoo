#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process_generator.h"

void* processGenerator(void* arg) {
    ProcessGeneratorArgs* args = (ProcessGeneratorArgs*)arg;
    int frequency = args->frequency;
    Process** processes = args->processes;
    int numProcesses = args->numProcesses;
    int timeSlice = args->timeSlice;
    PriorityQueue* pq = args->pq;
    pthread_t schedulerThread = args->schedulerThread;

    int i = 0;
    while (1) {
        Process* process = createProcess(i + numProcesses + 1, rand() % 5 + 1, rand() % 20 + 1);
        insertProcess(pq, process);
        printf("Generated process %d with priority %d and execution time %d\n", process->processId, process->priority, process->executionTime);

        i++;
        sleep(frequency);

        if (pthread_kill(schedulerThread, 0) != 0) {
            break; // If scheduler thread is not alive, stop process generation
        }
    }

    pthread_exit(NULL);
}
