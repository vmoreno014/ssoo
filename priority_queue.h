#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "process.h"
#include <pthread.h>

typedef struct {
    Process** heap;
    int size;
    int capacity;
    pthread_mutex_t lock;
} PriorityQueue;

PriorityQueue* initPriorityQueue(int capacity);
void destroyPriorityQueue(PriorityQueue* pq);
void swap(Process** a, Process** b);
void heapify(PriorityQueue* pq, int index);
void insertProcess(PriorityQueue* pq, Process* process);
Process* removeHighestPriorityProcess(PriorityQueue* pq);

#endif /* PRIORITY_QUEUE_H */
