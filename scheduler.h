#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include "priority_queue.h"

typedef struct {
    Process** processes;
    int numProcesses;
    int timeSlice;
    PriorityQueue* pq;
} SchedulerArgs;

void* scheduleProcesses(void* arg);

#endif /* SCHEDULER_H */
