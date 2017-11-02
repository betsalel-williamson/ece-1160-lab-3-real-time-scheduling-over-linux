#include<stdio.h>                      // A execution time 10, period: 20
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG
#endif

#define TEST1

#ifdef DEBUG

#ifdef TEST1
#define INPUT_PERIOD_A  10
#define EXECUTION_A     25
#define INPUT_PERIOD_B  25
#define EXECUTION_B     60
#endif

#ifdef TEST2
#define INPUT_PERIOD_A  20
#define EXECUTION_A     50
#define INPUT_PERIOD_B  35
#define EXECUTION_B     100
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
//                        /* These options don’t set a flag.
//                           We distinguish them by their indices. */
//                        {"firstTrace",     required_argument,       0, 'a'},
//                        {"secondTrace",  required_argument,       0, 'b'}
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
//                /* If this option set a flag, do nothing else now. */
//                if (long_options[option_index].flag != 0)
//                    break;
//                printf ("option %s", long_options[option_index].name);
//                if (optarg)
//                    printf (" with arg %s", optarg);
//                printf ("\n");
//                break;
//
//            case 'a':
//                printf ("option -a with value `%s'\n", optarg);
//                break;
//            case 'b':
//                printf ("option -b with value `%s'\n", optarg);
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

    int A, B;                           //arrival time of process A and B
    int cycA, cycB, serveA, serveB;         //period and execution for A and B processes
    float m;
    int i, j, a = 0, b = 0, ka = 0, kb = 0;                 /*ka,kb is a switch and
 											i, j, a, b, to record status of each process*/
    int numa = 0, numb = 0;                         //accumulated execution time
    int T;

    printf("\t\t\t------------------------------------------------\n");
    printf("\t\t\trate monotonic schedule algorithm\n");
    printf("\t\t\t------------------------------------------------\n");

//    printf("please input period and execution for A process\n");
//    scanf("%d%d", &cycA, &serveA);
//    printf("please input period and execution for B process\n");
//    scanf("%d%d", &cycB, &serveB);

    cycA = INPUT_PERIOD_A;
    serveA = EXECUTION_A;

    cycB = INPUT_PERIOD_B;
    serveB = EXECUTION_B;

    printf("period and execution for A process: %d %d\n", cycA, serveA);
    printf("period and execution for B process: %d %d\n", cycB, serveB);

    m = (float) serveA / cycA + (float) serveB / cycB;


    for (T = 0; T <= 100; T++) {

//        /* this block is to check if CPU can schedule*/
//        if () {
//            //please write the code for this block by yourself
//        }


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
    return EXIT_SUCCESS;
}
