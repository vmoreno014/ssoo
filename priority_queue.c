#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

PriorityQueue* initPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap = (Process**)malloc(capacity * sizeof(Process*));
    pq->size = 0;
    pq->capacity = capacity;
    pthread_mutex_init(&pq->lock, NULL);
    return pq;
}

void destroyPriorityQueue(PriorityQueue* pq) {
    free(pq->heap);
    pthread_mutex_destroy(&pq->lock);
    free(pq);
}

void swap(Process** a, Process** b) {
    Process* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->heap[left]->priority < pq->heap[smallest]->priority)
        smallest = left;

    if (right < pq->size && pq->heap[right]->priority < pq->heap[smallest]->priority)
        smallest = right;

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heapify(pq, smallest);
    }
}

void insertProcess(PriorityQueue* pq, Process* process) {
    pthread_mutex_lock(&pq->lock);

    if (pq->size == pq->capacity) {
        printf("Priority Queue is full. Cannot insert process.\n");
        pthread_mutex_unlock(&pq->lock);
        return;
    }

    pq->heap[pq->size] = process;
    int i = pq->size;
    pq->size++;

    while (i != 0 && pq->heap[(i - 1) / 2]->priority > pq->heap[i]->priority) {
        swap(&pq->heap[(i - 1) / 2], &pq->heap[i]);
        i = (i - 1) / 2;
    }

    pthread_mutex_unlock(&pq->lock);
}

Process* removeHighestPriorityProcess(PriorityQueue* pq) {
    pthread_mutex_lock(&pq->lock);

    if (pq->size == 0) {
        printf("Priority Queue is empty. No processes to remove.\n");
        pthread_mutex_unlock(&pq->lock);
        return NULL;
    }

    Process* process = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    pthread_mutex_unlock(&pq->lock);

    return process;
}
