#include <stdio.h>
#include <pthread.h>
#include "scheduler.h"

void* scheduleProcesses(void* arg) {
    SchedulerArgs* args = (SchedulerArgs*)arg;
    Process** processes = args->processes;
    int numProcesses = args->numProcesses;
    int timeSlice = args->timeSlice;
    PriorityQueue* pq = args->pq;

    int i;
    for (i = 0; i < numProcesses; i++) {
        insertProcess(pq, processes[i]);
    }

    int currentTime = 0;
    int remainingProcesses = numProcesses;

    while (remainingProcesses > 0) {
        Process* currentProcess = removeHighestPriorityProcess(pq);

        if (currentProcess->executionTime <= timeSlice) {
            printf("Executing process %d for %d units of time.\n", currentProcess->processId, currentProcess->executionTime);
            executeProcess(currentProcess);
            currentTime += currentProcess->executionTime;
            currentProcess->executionTime = 0;
            remainingProcesses--;
        } else {
            printf("Executing process %d for %d units of time.\n", currentProcess->processId, timeSlice);
            executeProcess(currentProcess);
            currentProcess->executionTime -= timeSlice;
            currentTime += timeSlice;
        }

        while (i < numProcesses && processes[i]->priority <= currentTime) {
            insertProcess(pq, processes[i]);
            i++;
        }

        if (currentProcess->executionTime > 0) {
            insertProcess(pq, currentProcess);
        } else {
            destroyProcess(currentProcess);
        }
    }

    pthread_exit(NULL);
}
