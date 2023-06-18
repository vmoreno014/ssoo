#include <stdio.h>
#include <stdlib.h>
#include "process.h"

Process* createProcess(int id, int priority, int executionTime) {
    Process* process = (Process*)malloc(sizeof(Process));
    process->processId = id;
    process->priority = priority;
    process->executionTime = executionTime;
    return process;
}

void destroyProcess(Process* process) {
    free(process);
}

void executeProcess(Process* process) {
    printf("Executing process %d\n", process->processId);
    // Simulate execution time
    int i;
    for (i = 0; i < process->executionTime; i++) {
        // Do some work
    }
    printf("Process %d completed\n", process->processId);
}
