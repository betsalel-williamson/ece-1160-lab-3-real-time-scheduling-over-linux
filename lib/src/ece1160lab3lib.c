//
// Created by School on 11/1/17.
//

#include <stdio.h>

#include "ece1160lab3lib.h"

typedef struct ProcessInformation {
    int *period;
    int *timeRequiredToExecute;
    int *processIteration;
    int *timeCompleted;

    int (*isProcessFinished)(int, int);

    int (*isProcessRunning)(int *);
} process;

int isProcessRunning(const int *running) {
    return *running == 1;
}

int isProcessFinished(int timeLeft, int timeRequiredToExecute) {
    return timeLeft == timeRequiredToExecute + 1;
}

void
EDFStrategy(int serveA, int cycA, int numa, int a, int *ka, int serveB, int cycB, int numb, int b, int *kb, int T) {

    int timeLeftForA = serveA - numa;
    int isAFinished = numa == serveA + 1;
    int isARunning = *ka == 1;
    int timeLeftForB = serveB - numb;
    int isBFinished = numb == serveB + 1;
    int isBRunning = *kb == 1;

    if (isBRunning && !isAFinished && timeLeftForA < timeLeftForB) {
        printf("when T=%d, ", T);
        printf("time left for A%d is %d,", a, timeLeftForA);
        printf("time left for B%d is %d,", b, timeLeftForB);
        printf("run process A%d\n", a);
        *kb = 0;
        *ka = 1;
    } else if (isARunning && !isBFinished && timeLeftForB < timeLeftForA) {
        printf("when T=%d, ", T);
        printf("time left for A%d is %d,", a, timeLeftForA);
        printf("time left for B%d is %d,", b, timeLeftForB);
        printf("run process B%d\n", b);
        *kb = 1;
        *ka = 0;
    } else {
        // do nothing
    }
}

void
RMSStrategy(int serveA, int cycA, int numa, int a, int *ka, int serveB, int cycB, int numb, int b, int *kb, int T) {

    int periodOfA = cycA;
    int timeLeftForA = serveA - numa;
    int isAFinished = numa == serveA + 1;
    int isARunning = *ka == 1;

    int periodOfB = cycB;
    int timeLeftForB = serveB - numb;
    int isBFinished = numb == serveB + 1;
    int isBRunning = *kb == 1;

    if (isBRunning && !isAFinished && periodOfA < periodOfB) {
        printf("when T=%d, ", T);
        printf("time left for A%d is %d,", a, timeLeftForA);
        printf("time left for B%d is %d,", b, timeLeftForB);
        printf("run process A%d\n", a);
        *kb = 0;
        *ka = 1;
    } else if (isARunning && !isBFinished && periodOfB < periodOfA) {
        printf("when T=%d, ", T);
        printf("time left for A%d is %d,", a, timeLeftForA);
        printf("time left for B%d is %d,", b, timeLeftForB);
        printf("run process B%d\n", b);
        *kb = 1;
        *ka = 0;
    } else {
        // do nothing
    }

//    /* this block is to check if CPU can schedule*/
//    // if the period of A is less than B then it should have priority.
//    if (cycA < cycB) {
//        printf("time left for A%d is %d,", a, timeLeftForA);
//        printf("time left for B%d is %d,", b, timeLeftForB);
//        *kb = 0;
//        *ka = 1;
//        //please write the code for this block by yourself
//    } else {
//        printf("time left for A%d is %d,", a, timeLeftForA);
//        printf("time left for B%d is %d,", b, timeLeftForB);
//        *kb = 1;
//        *ka = 0;
//    }

//    int isAFinished = numa == serveA + 1;
//    int isBFinished = numb == serveB + 1;
//
//    if (*kb == 1 && !isAFinished && cycA < cycB) {
//        printf("when T=%d, ", T);
//        printf("run process A%d\n", a);
//        *kb = 0;
//        *ka = 1;
//    } else if (*ka == 1 && !isBFinished && cycB < cycA) {
//        printf("when T=%d, ", T);
//        printf("run process B%d\n", b);
//        *kb = 1;
//        *ka = 0;
//    } else {
//        // do nothing
//    }
}

void
runSchedulingProgram(int serveA, int cycA, int serveB, int cycB, schedulingStrategy strategy, const char *algoName) {
    process p1, p2;

    int A, B;                           //arrival time of process A and B
//    int cycA, cycB, serveA, serveB;         //period and execution for A and B processes
    float m;
    int i, j, a = 0, b = 0, ka = 0, kb = 0;                 /*ka,kb is a switch and
 											i, j, a, b, to record status of each process*/
    int numa = 0, numb = 0;                         //accumulated execution time
    int T;
    printf("\t\t\t------------------------------------------------\n");
    printf("\t\t\t\t%s schedule algorithm\n", algoName);
    printf("\t\t\t------------------------------------------------\n");

    p1.period = &cycA;
    p1.timeRequiredToExecute = &serveA;
    p1.isProcessRunning = isProcessRunning(&ka);

            printf("Process A runs every %d seconds and needs %d seconds to finish\n", cycA, serveA);
    printf("Process B runs every %d seconds and needs %d seconds to finish\n", cycB, serveB);

    m = (float) serveA / cycA + (float) serveB / cycB;

    for (T = 0; T <= 100; T++) {

        /* this block is to check if CPU can schedule*/
        // if the period of A is less than B then it should have priority.

        strategy(serveA, cycA, numa, a, &ka, serveB, cycB, numb, b, &kb, T);

        ///////// DON'T MODIFY THE CODE BELOW //////////

        /* this block is to say that process A has been done*/
        /* but process B has not been done yet*/
        if (numa == serveA)                                        //process A is done
        {
            numa = serveA + 1;
            printf("when T=%d, ", T);
            printf("process A%d is done\n", a);
            if (numb < serveB) {
                printf("run process B%d\n", b);
                kb = 1;
            }
            ka = 0;
        }

        /* this block is to say that process B has been done*/
        /* but process A has not been done yet*/
        if (numb == serveB) {
            numb = serveB + 1;
            printf("when T=%d, ", T);
            printf("process B%d is done\n", b);
            if (numa < serveA) {
                printf("run process A%d\n", a);
                ka = 1;
            }
            kb = 0;
        }

        /* this block start running the process*/
        if (T % cycA == 0 && T % cycB == 0) {
            A = B = T;
            j = ++a;
            i = ++b;
            printf("when T=%d, process A%d and process B%d are generated together\n", T, j, i);
            if (cycA <= cycB) // deadline is cycle
            {
                printf("run process A%d and suspend process B%d\n", j, i);
                printf("---------------------------------------\n");
                ka = 1;
                kb = 0;
            } else {
                printf("run process B%d and suspend process A%d\n", i, j);
                ka = 0;
                kb = 1;
            }
            numa = numb = 0;
        }


        /* this block initializes A another new period*/
        if (T % cycA == 0 && T % cycB != 0) {
            A = T;
            printf("when T=%d, ", T);
            printf("process A%d is generated\n", ++a);   //impossible to compete with A
            numa = 0;
            if (numb < serveB) {                //process B is unfinished yet
                if (cycB > cycA) {
                    printf("run process A%d\n", a);
                    ka = 1;
                    kb = 0;
                } else {                     //period of B is earlier than period of A
                    printf("process B%d is moving forward\n", b);
                }
            } else                                   //process B is done, just run A
            {
                printf("process A%d is run\n", a);
                ka = 1;
            }
        }


        /* this block initializes B another new period*/
        if (T % cycA != 0 && T % cycB == 0) {
            B = T;
            printf("when T=%d, ", T);
            printf("process B%d is generated\n", ++b);            //impossible to compete with B
            numb = 0;
            if (numa < serveA) {                         //process A is undone yet
                if (cycB >= cycA) {
                    printf("process A%d is on run\n", a);
                } else {
                    printf("process B%d is to run\n", b);
                    kb = 1;
                    ka = 0;
                }
            } else                                //process A is done
            {
                printf("process B%d is on run\n", b);
                kb = 1;
            }
        }


        /* this block is to accumulate running time*/
        if (ka) {
            numa++;
        }
        if (kb) {
            numb++;
        }
    }
}

void runEDF(int serveA, int cycA, int serveB, int cycB) {

    int A, B;                           //arrival time of process A and B
//    int cycA, cycB, serveA, serveB;         //period and execution for A and B processes
    float m;
    int i, j, a = 0, b = 0, ka = 0, kb = 0;                 /*ka,kb is a switch and
 											i, j, a, b, to record status of each process*/
    int numa = 0, numb = 0;                         //accumulated execution time
    int T;
    printf("\t\t\t------------------------------------------------\n");
    printf("\t\t\t\tearliest deadline first schedule algorithm\n");
    printf("\t\t\t------------------------------------------------\n");
    printf("Process A runs every %d seconds and needs %d seconds to finish\n", cycA, serveA);
    printf("Process B runs every %d seconds and needs %d seconds to finish\n", cycB, serveB);

//    printf("please input period and execution for A process\n");
//    scanf("%d%d", &cycA, &serveA);
//    printf("please input period and execution for B process\n");
//    scanf("%d%d", &cycB, &serveB);

//    cycA = INPUT_PERIOD_P1;
//    serveA = EXECUTION_P1;
//
//    cycB = INPUT_PERIOD_P2;
//    serveB = EXECUTION_P2;

    m = (float) serveA / cycA + (float) serveB / cycB;


    for (T = 0; T <= 100; T++) {

        /* this block is to check if CPU can schedule*/
        // if the period of A is less than B then it should have priority.

        int timeLeftForA = serveA - numa;
        int isAFinished = numa == serveA + 1;
        int timeLeftForB = serveB - numb;
        int isBFinished = numb == serveB + 1;

        if (ka == 1 && !isBFinished && timeLeftForB < timeLeftForA) {
            printf("when T=%d, ", T);
            printf("run process B%d\n", b);
            kb = 1;
            ka = 0;
        } else if (kb == 1 && !isAFinished && timeLeftForA < timeLeftForB) {
            printf("when T=%d, ", T);
            printf("run process A%d\n", a);
            kb = 0;
            ka = 1;
        }

        ///////// DON'T MODIFY THE CODE BELOW //////////

        /* this block is to say that process A has been done*/
        /* but process B has not been done yet*/
        if (numa == serveA)                                        //process A is done
        {
            numa = serveA + 1;
            printf("when T=%d, ", T);
            printf("process A%d is done\n", a);
            if (numb < serveB) {
                printf("run process B%d\n", b);
                kb = 1;
            }
            ka = 0;
        }

        /* this block is to say that process B has been done*/
        /* but process A has not been done yet*/
        if (numb == serveB) {
            numb = serveB + 1;
            printf("when T=%d, ", T);
            printf("process B%d is done\n", b);
            if (numa < serveA) {
                printf("run process A%d\n", a);
                ka = 1;
            }
            kb = 0;
        }

        /* this block start running the process*/
        if (T % cycA == 0 && T % cycB == 0) {
            A = B = T;
            j = ++a;
            i = ++b;
            printf("when T=%d, process A%d and process B%d are generated together\n", T, j, i);
            if (cycA <= cycB) // deadline is cycle
            {
                printf("run process A%d and suspend process B%d\n", j, i);
                printf("---------------------------------------\n");
                ka = 1;
                kb = 0;
            } else {
                printf("run process B%d and suspend process A%d\n", i, j);
                ka = 0;
                kb = 1;
            }
            numa = numb = 0;
        }


        /* this block initializes A another new period*/
        if (T % cycA == 0 && T % cycB != 0) {
            A = T;
            printf("when T=%d, ", T);
            printf("process A%d is generated\n", ++a);   //impossible to compete with A
            numa = 0;
            if (numb < serveB) {                //process B is unfinished yet
                if (cycB > cycA) {
                    printf("run process A%d\n", a);
                    ka = 1;
                    kb = 0;
                } else {                     //period of B is earlier than period of A
                    printf("process B%d is moving forward\n", b);
                }
            } else                                   //process B is done, just run A
            {
                printf("process A%d is run\n", a);
                ka = 1;
            }
        }


        /* this block initializes B another new period*/
        if (T % cycA != 0 && T % cycB == 0) {
            B = T;
            printf("when T=%d, ", T);
            printf("process B%d is generated\n", ++b);            //impossible to compete with B
            numb = 0;
            if (numa < serveA) {                         //process A is undone yet
                if (cycB >= cycA) {
                    printf("process A%d is on run\n", a);
                } else {
                    printf("process B%d is to run\n", b);
                    kb = 1;
                    ka = 0;
                }
            } else                                //process A is done
            {
                printf("process B%d is on run\n", b);
                kb = 1;
            }
        }


        /* this block is to accumulate running time*/
        if (ka) {
            numa++;
        }
        if (kb) {
            numb++;
        }
    }
}

void runRMS(int serveA, int cycA, int serveB, int cycB) {

    int A, B;                           //arrival time of process A and B
//    int cycA, cycB, serveA, serveB;         //period and execution for A and B processes
    float m;
    int i, j, a = 0, b = 0, ka = 0, kb = 0;                 /*ka,kb is a switch and
 											i, j, a, b, to record status of each process*/
    int numa = 0, numb = 0;                         //accumulated execution time
    int T;
    printf("\t\t\t------------------------------------------------\n");
    printf("\t\t\t\trate monotonic schedule algorithm\n");
    printf("\t\t\t------------------------------------------------\n");
//    printf("please input period and execution for A process\n");
//    scanf("%d%d", &cycA, &serveA);
//    printf("please input period and execution for B process\n");
//    scanf("%d%d", &cycB, &serveB);

//    cycA = INPUT_PERIOD_P1;
//    serveA = EXECUTION_P1;
//
//    cycB = INPUT_PERIOD_P2;
//    serveB = EXECUTION_P2;

    m = (float) serveA / cycA + (float) serveB / cycB;


    for (T = 0; T <= 100; T++) {

        /* this block is to check if CPU can schedule*/
        // if the period of A is less than B then it should have priority.
        if (cycA < cycB) {
            kb = 0;
            ka = 1;
            //please write the code for this block by yourself
        } else {
            kb = 1;
            ka = 0;
        }

        ///////// DON'T MODIFY THE CODE BELOW //////////

        /* this block is to say that process A has been done*/
        /* but process B has not been done yet*/
        if (numa == serveA)                                        //process A is done
        {
            numa = serveA + 1;
            printf("when T=%d, ", T);
            printf("process A%d is done\n", a);
            if (numb < serveB) {
                printf("run process B%d\n", b);
                kb = 1;
            }
            ka = 0;
        }

        /* this block is to say that process B has been done*/
        /* but process A has not been done yet*/
        if (numb == serveB) {
            numb = serveB + 1;
            printf("when T=%d, ", T);
            printf("process B%d is done\n", b);
            if (numa < serveA) {
                printf("run process A%d\n", a);
                ka = 1;
            }
            kb = 0;
        }

        /* this block start running the process*/
        if (T % cycA == 0 && T % cycB == 0) {
            A = B = T;
            j = ++a;
            i = ++b;
            printf("when T=%d, process A%d and process B%d are generated together\n", T, j, i);
            if (cycA <= cycB) // deadline is cycle
            {
                printf("run process A%d and suspend process B%d\n", j, i);
                printf("---------------------------------------\n");
                ka = 1;
                kb = 0;
            } else {
                printf("run process B%d and suspend process A%d\n", i, j);
                ka = 0;
                kb = 1;
            }
            numa = numb = 0;
        }


        /* this block initializes A another new period*/
        if (T % cycA == 0 && T % cycB != 0) {
            A = T;
            printf("when T=%d, ", T);
            printf("process A%d is generated\n", ++a);   //impossible to compete with A
            numa = 0;
            if (numb < serveB) {                //process B is unfinished yet
                if (cycB > cycA) {
                    printf("run process A%d\n", a);
                    ka = 1;
                    kb = 0;
                } else {                     //period of B is earlier than period of A
                    printf("process B%d is moving forward\n", b);
                }
            } else                                   //process B is done, just run A
            {
                printf("process A%d is run\n", a);
                ka = 1;
            }
        }


        /* this block initializes B another new period*/
        if (T % cycA != 0 && T % cycB == 0) {
            B = T;
            printf("when T=%d, ", T);
            printf("process B%d is generated\n", ++b);            //impossible to compete with B
            numb = 0;
            if (numa < serveA) {                         //process A is undone yet
                if (cycB >= cycA) {
                    printf("process A%d is on run\n", a);
                } else {
                    printf("process B%d is to run\n", b);
                    kb = 1;
                    ka = 0;
                }
            } else                                //process A is done
            {
                printf("process B%d is on run\n", b);
                kb = 1;
            }
        }


        /* this block is to accumulate running time*/
        if (ka) {
            numa++;
        }
        if (kb) {
            numb++;
        }
    }
}