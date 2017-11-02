//
// Created by School on 11/1/17.
//

#ifndef ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H
#define ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H

typedef void (*strategy)(int serveA, int cycA, int numa, int a, int *ka, int serveB, int cycB, int numb, int b, int *kb,
                         int T);

void EDFStrategy(int serveA, int cycA, int numa, int a, int *ka, int serveB, int cycB, int numb, int b, int *kb, int T);

void RMSStrategy(int serveA, int cycA, int numa, int a, int *ka, int serveB, int cycB, int numb, int b, int *kb, int T);

void runProgram(int serveA, int cycA, int serveB, int cycB, strategy algoMethod, const char * algoName);

void runEDF(int serveA, int cycA, int serveB, int cycB);

void runRMS(int serveA, int cycA, int serveB, int cycB);

#endif //ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_DUMMY_H
