#include "priorityInversion.h"
#include "ece1160lab3lib.h"

void printDashedLine();

int main() {

    runSchedulingProgram(10, 25, 15, 60, RMSStrategy, "RMSStrategy");
    runSchedulingProgram(20, 50, 35, 100, RMSStrategy, "RMSStrategy");
    runSchedulingProgram(20, 50, 35, 40, RMSStrategy, "RMSStrategy");
    printDashedLine();

    runSchedulingProgram(10, 20, 25, 50, EDFStrategy, "EDFStrategy");
    runSchedulingProgram(25, 50, 35, 80, EDFStrategy, "EDFStrategy");

    printDashedLine();

    runPriorityInversion();
    return 0;
}

void printDashedLine() {
    printf("----------------------------------------\n");
}