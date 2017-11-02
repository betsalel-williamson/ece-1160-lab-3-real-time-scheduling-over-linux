#include<stdio.h>                      // A execution time 10, period: 20
#include <stdlib.h>
#include <mach/boolean.h>

#ifndef DEBUG
#define DEBUG
#endif

#define TEST2

#ifdef DEBUG

#ifdef TEST1
#define EXECUTION_P1     10
#define INPUT_PERIOD_P1  25
#define EXECUTION_P2     15
#define INPUT_PERIOD_P2  60
#endif

#ifdef TEST2
#define EXECUTION_P1     20
#define INPUT_PERIOD_P1  50
#define EXECUTION_P2     35
#define INPUT_PERIOD_P2  100
#endif

#endif

#ifndef ERROR
#define ERROR -1
#endif

/* Flag set by ‘--verbose’. */
static int verbose_flag;

// B execution time 25, period: 50
int main(int argc, const char *argv[]) {

//    int c;
//
//    while (1)
//    {
//        static struct option long_options[] =
//                {
//                        /* These options don’t set p1 flag.
//                           We distinguish them by their indices. */
//                        {"firstTrace",     required_argument,       0, 'p1'},
//                        {"secondTrace",  required_argument,       0, 'p2'}
//                };
//        /* getopt_long stores the option index here. */
//        int option_index = 0;
//
//        c = getopt_long (argc, (char *const *) argv, "ab:",
//                         long_options, &option_index);
//
//        /* Detect the end of the options. */
//        if (c == -1)
//            break;
//
//        switch (c)
//        {
//            case 0:
//                /* If this option set p1 flag, do nothing else now. */
//                if (long_options[option_index].flag != 0)
//                    break;
//                printf ("option %s", long_options[option_index].name);
//                if (optarg)
//                    printf (" with arg %s", optarg);
//                printf ("\n");
//                break;
//
//            case 'p1':
//                printf ("option -p1 with value `%s'\n", optarg);
//                break;
//            case 'p2':
//                printf ("option -p2 with value `%s'\n", optarg);
//                break;
//            case '?':
//                /* getopt_long already printed an error message. */
//                break;
//
//            default:
//                abort ();
//        }
//    }
//
//    /* Instead of reporting ‘--verbose’
//       and ‘--brief’ as they are encountered,
//       we report the final status resulting from them. */
//    if (verbose_flag)
//        puts ("verbose flag is set");
//
//    /* Print any remaining command line arguments (not options). */
//    if (optind < argc)
//    {
//        printf ("non-option ARGV-elements: ");
//        while (optind < argc)
//            printf ("%s ", argv[optind++]);
//        putchar ('\n');
//    }    printf("\n");
//
//    for (int i=1; i<argc; i++) {
//        printf("%s\n",argv[i]);
//
//
//    }


    // if we don't have any input then ask for input

    int A, B;                           //arrival time of process P1  and B
    int input_period_p1, input_period_p2, exec_p1, exec_p2;         //period and execution for A and B processes
    float m;
    int i, j, p1 = 0, p2 = 0, is_p1_running = 0, is_p2_running = FALSE;                 /*is_p1_running,is_p2_running is p1 switch and
 											i, j, p1, p2, to record status of each process*/
    int p1_accumulated_execution_time = 0, p2_accumulated_execution_time = 0;                         //accumulated execution time
    int T;

    printf("\t\t\t------------------------------------------------\n");
    printf("\t\t\trate monotonic schedule algorithm\n");
    printf("\t\t\t------------------------------------------------\n");

//    printf("please input period and execution for A process\n");
//    scanf("%d%d", &input_period_p1, &exec_p1);
//    printf("please input period and execution for B process\n");
//    scanf("%d%d", &input_period_p2, &exec_p2);

    input_period_p1 = INPUT_PERIOD_P1;
    exec_p1 = EXECUTION_P1;

    input_period_p2 = INPUT_PERIOD_P2;
    exec_p2 = EXECUTION_P2;

    printf("Process P1 will run every %d seconds and require %d seconds to complete.\n", input_period_p1, exec_p1);
    printf("Process P2 will run every %d seconds and require %d seconds to complete.\n", input_period_p2, exec_p2);

    m = (float) exec_p1 / input_period_p1 + (float) exec_p2 / input_period_p2;


    for (T = 0; T <= 100; T++) {

        /* this block is to say that process P1  has been done*/
        /* but process P2  has not been done yet*/
        if (p1_accumulated_execution_time == exec_p1)                                        //process P1  is done
        {
            printf("T=%d, ", T);
            p1_accumulated_execution_time = exec_p1 + 1;
            printf("process P1 %d is done\n", p1);

            // p2 hasn't finished yet
            if (p2_accumulated_execution_time < exec_p2) {
                printf("run process P2 %d\n", p2);
                is_p2_running = TRUE;
            }
            is_p1_running = FALSE;
        }

        /* this block is to say that process P2  has been done*/
        /* but process P1  has not been done yet*/
        if (p2_accumulated_execution_time == exec_p2) {
            p2_accumulated_execution_time = exec_p2 + 1;
            printf("when T=%d, ", T);
            printf("process P2 %d is done\n", p2);

            // p1 hasn't finished yet
            if (p1_accumulated_execution_time < exec_p1) {
                printf("run process P1 %d\n", p1);
                is_p1_running = TRUE;
            }
            is_p2_running = FALSE;
        }

        /* this block start running the process*/
        if (T % input_period_p1 == 0 && T % input_period_p2 == 0) {
            A = B = T;
            j = ++p1;
            i = ++p2;
            printf("process P1 %d and process P2 %d are generated together\n", T, j, i);
            if (input_period_p1 <= input_period_p2) // deadline is cycle
            {
                printf("run process P1 %d and suspend process P2 %d\n", j, i);
                printf("---------------------------------------\n");
                is_p1_running = TRUE;
                is_p2_running = FALSE;
            } else {
                printf("run process P2 %d and suspend process P1 %d\n", i, j);
                is_p1_running = FALSE;
                is_p2_running = TRUE;
            }
            p1_accumulated_execution_time = p2_accumulated_execution_time = 0;
        }


        /* this block initializes P1 another new period*/
        if (T % input_period_p1 == 0 && T % input_period_p2 != 0) {
            A = T;
            printf("when T=%d, ", T);
            printf("process P1 %d is generated\n", ++p1);
            p1_accumulated_execution_time = 0;

            if (input_period_p1 < input_period_p2) {
                printf("process P1 %d is on run\n", p1);
                is_p1_running = TRUE;
                is_p2_running = FALSE;

            } else
            {
                printf("process P2 %d is on run\n", p2);
                is_p1_running = FALSE;
                is_p2_running = TRUE;
            }
        }


        /* this block initializes P2 another new period*/
        if (T % input_period_p1 != 0 && T % input_period_p2 == 0) {
            B = T;
            printf("when T=%d, ", T);
            printf("process P2 %d is generated\n", ++p2);
            p2_accumulated_execution_time = 0;

            if (input_period_p2 < input_period_p1) {
                printf("process P2 %d is on run\n", p2);
                is_p1_running = FALSE;
                is_p2_running = TRUE;

            } else
            {
                printf("process P1 %d is on run\n", p1);
                is_p1_running = TRUE;
                is_p2_running = FALSE;
            }
        }


        /* this block is to accumulate running time*/
        if (is_p1_running) {
            p1_accumulated_execution_time++;
        }
        if (is_p2_running) {
            p2_accumulated_execution_time++;
        }

//    puts("\n");
    }
    return EXIT_SUCCESS;
}
