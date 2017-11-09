//
// Created by School on 11/1/17.
//

#ifndef ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H
#define ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct process {
    int *timeNeeded; // serveA
    int *timeCompleted; // numa
    int *period; // cycA
    int *iteration; // a
    int *isRunning; // *ka
} process;

int processDoesntContainNull(process *process);

typedef void (*schedulingStrategy)(process *processA, process *processB, int timeElapsed);

void EDFStrategy(process *processA, process *processB, int timeElapsed);

void RMSStrategy(process *processA, process *processB, int timeElapsed);

void
runSchedulingProgram(int serveA, int cycA, int serveB, int cycB, schedulingStrategy strategy, const char *algoName);

void runEDF(int serveA, int cycA, int serveB, int cycB);

void runRMS(int serveA, int cycA, int serveB, int cycB);

#endif //ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H
