
#include "ece1160lab3lib.h"

/* Section 2 of Project */
/**
 * Use Pthreads to create a working example of priority inversion and inheritance
 */

//
//void function()
//{
//    //do some work here.
//}
//
//void funtion1()
//{
//    //function 1 for thread 1.
//    //do some work here
//}
//
//void function2()
//{
////function 2 for thread 2.
////do some work here and call function()
//}
//
//void function3()
//{
////function 3 for thread 3.
////do some work here
//}
//
//void main()
//{
//    //create mutex and initialize it.
////create thread 1, thread 2 and thread 3
////set different priority for each thread
////set handler for thread 1, thread 2 and thread 3 respectively. For instance, function 1 for thread 1, function 2 for thread 2 and function 3 for thread 3
//}

int main() {

    runSchedulingProgram(10, 25, 15, 60, RMSStrategy, "RMSStrategy");
    runSchedulingProgram(20, 50, 35, 100, RMSStrategy, "RMSStrategy");
    runSchedulingProgram(20, 50, 35, 40, RMSStrategy, "RMSStrategy");

    runSchedulingProgram(10, 20, 25, 50, EDFStrategy, "EDFStrategy");
    runSchedulingProgram(25, 50, 35, 80, EDFStrategy, "EDFStrategy");

    return 0;
}