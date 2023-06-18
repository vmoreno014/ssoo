#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "process.h"
#include "priority_queue.h"
#include "scheduler.h"
#include "process_generator.h"

int main() {
    // Create some processes
    Process* process1 = createProcess(1, 3, 10);
    Process* process2 = createProcess(2, 1, 5);
    Process* process3 = createProcess(3, 2, 7);

    // Put processes into an array
    Process* processes[] = { process1, process2, process3 };
    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    // Create a priority queue
    int capacity = 10; // Set the capacity as needed
    PriorityQueue* pq = initPriorityQueue(capacity);

    // Create scheduler arguments
    SchedulerArgs* schedulerArgs = (SchedulerArgs*)malloc(sizeof(SchedulerArgs));
    schedulerArgs->processes = processes;
    schedulerArgs->numProcesses = numProcesses;
    schedulerArgs->timeSlice = 4;
    schedulerArgs->pq = pq;

    // Create a thread for process scheduling
    pthread_t schedulerThread;
    pthread_create(&schedulerThread, NULL, scheduleProcesses, (void*)schedulerArgs);

    // Create process generator arguments
    ProcessGeneratorArgs* generatorArgs = (ProcessGeneratorArgs*)malloc(sizeof(ProcessGeneratorArgs));
    generatorArgs->frequency = 2; // Set the frequency as needed
    generatorArgs->processes = processes;
    generatorArgs->numProcesses = numProcesses;
    generatorArgs->timeSlice = 4;
    generatorArgs->pq = pq;
    generatorArgs->schedulerThread = schedulerThread;

    // Create a thread for process generation
    pthread_t generatorThread;
    pthread_create(&generatorThread, NULL, processGenerator, (void*)generatorArgs);

    // Wait for the process generation thread to finish
    pthread_join(generatorThread, NULL);

    // Clean up
    int i;
    for (i = 0; i < numProcesses; i++) {
        destroyProcess(processes[i]);
    }
    destroyPriorityQueue(pq);
    free(schedulerArgs);
    free(generatorArgs);

    return 0;
}
