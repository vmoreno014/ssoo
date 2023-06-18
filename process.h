#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int processId;
    int priority;
    int executionTime;
} Process;

Process* createProcess(int id, int priority, int executionTime);
void destroyProcess(Process* process);
void executeProcess(Process* process);

#endif /* PROCESS_H */
