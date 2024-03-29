//Implement the shortest job first scheduling algorithm.
#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes Burst time Waiting time Turnaround time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d ", processes[i]);
        printf("    %d ", bt[i]);
        printf("    %d", wt[i]);
        printf("    %d\n", tat[i]);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average waiting time = %f", avg_wt);
    printf("\nAverage turnaround time = %f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {10, 5, 8};

    findavgTime(processes, n, burst_time);
    return 0;
}

// Output:
// @cloudshell:~$ nano sjf.c
// @cloudshell:~$ gcc sjf.c -o sjf
// @cloudshell:~$ ./sjf
// Processes Burst time Waiting time Turnaround time
//  1     10     0    10
//  2     5     10    15
//  3     8     15    23
// Average waiting time = 8.333333
// Average turnaround time = 16.000000