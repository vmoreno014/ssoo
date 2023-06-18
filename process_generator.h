#ifndef PROCESS_GENERATOR_H
#define PROCESS_GENERATOR_H

#include "process.h"
#include "priority_queue.h"
#include <pthread.h>

typedef struct {
    int frequency;
    Process** processes;
    int numProcesses;
    int timeSlice;
    PriorityQueue* pq;
    pthread_t schedulerThread;
} ProcessGeneratorArgs;

void* processGenerator(void* arg);

#endif /* PROCESS_GENERATOR_H */
