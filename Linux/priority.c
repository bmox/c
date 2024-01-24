// Implementing Priority Scheduling Algorithm
#include <stdio.h>

// Function to swap two variables
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform priority scheduling
void priorityScheduling(int processes[], int burst_time[], int priority[], int n) {
    int index[n];

    for (int i = 0; i < n; i++) {
        index[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        int a = priority[i], m = i;

        // Finding out the highest priority element and placing it at its desired position
        for (int j = i; j < n; j++) {
            if (priority[j] > a) {
                a = priority[j];
                m = j;
            }
        }

        // Swapping processes
        swap(&priority[i], &priority[m]);
        swap(&burst_time[i], &burst_time[m]);
        swap(&index[i], &index[m]);
    }

    // T stores the starting time of the process
    int t = 0;

    // Printing scheduled process
    printf("Order of process Execution is\n");
    for (int i = 0; i < n; i++) {
        printf("P%d is executed from %d to %d\n", index[i], t, t + burst_time[i]);
        t += burst_time[i];
    }
    printf("\n");
    printf("Process Id     Burst Time   Wait Time    TurnAround Time\n");
    int wait_time = 0;
    for (int i = 0; i < n; i++) {
        printf("P%-13d%-13d%-13d%-13d\n", index[i], burst_time[i], wait_time, wait_time + burst_time[i]);
        wait_time += burst_time[i];
    }
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {6, 8, 7, 3};
    int priority[] = {2, 1, 3, 4};

    priorityScheduling(processes, burst_time, priority, n);

    return 0;
}

// Output:
// @cloudshell:~$ nano priority.c
// @cloudshell:~$ gcc priority.c -o priority
// @cloudshell:~$ ./priority
// Order of process Execution is
// P4 is executed from 0 to 3
// P3 is executed from 3 to 10
// P1 is executed from 10 to 16
// P2 is executed from 16 to 24

// Process Id     Burst Time   Wait Time    TurnAround Time
// P4            3            0            3            
// P3            7            3            10           
// P1            6            10           16           
// P2            8            16           24   