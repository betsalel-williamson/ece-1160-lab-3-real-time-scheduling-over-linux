# ece-1160-lab-3-real-time-scheduling-over-linux

Original prompt can be seen at [link](lab-3-prompt.html) (updated on Nov 1, 2017 7:00 PM). Live link on cours webpage  can be seen [here](http://www.pitt.edu/~weigao/ece1160/fall2017/lab3.htm).

## Section 1

In this program, We assume that all threads run until at least both have completed one cycle.

Period means how often (in seconds) this thread will run. With a period of 3, process A will want to start every 3 seconds.

Execution says how many seconds the thread needs before it will complete. If A has a period of 5 and an execution of 4 that means that there will only be 1 second left every period to run other processes.

For RMS the priority does not change. EDF will change based on how long the process has been running.