//
// Created by School on 11/9/17.
//

#ifndef ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_PRIORITYINVERSION_H
#define ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_PRIORITYINVERSION_H

#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

int runPriorityInversion();

#endif //ECE_1160_LAB_3_REAL_TIME_SCHEDULING_OVER_LINUX_PRIORITYINVERSION_H
