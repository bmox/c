// Implementing FCFS Scheduling Algorithm
#include<stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    // Waiting time for the first process is 0
    wt[0] = 0;

    // Calculating waiting time
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("Processes Burst time Waiting time Turn around time\n");

    // Calculate total waiting time and total turn around time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t\t %d\t\t %d\t\t %d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    float avg_waiting_time = (float)total_wt / (float)n;
    float avg_turn_around_time = (float)total_tat / (float)n;

    printf("Average waiting time = %f\n", avg_waiting_time);
    printf("Average turn around time = %f\n", avg_turn_around_time);
}

// Driver code
int main() {
    // Process IDs
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];

    // Burst time of all processes
    int burst_time[] = {10, 5, 8};

    findavgTime(processes, n, burst_time);
    return 0;
}
//Output:
// @cloudshell:~$ nano fcfs.c
// @cloudshell:~$ gcc fcfs.c -o fcfs
// @cloudshell:~$ ./fcfs
// Processes Burst time Waiting time Turn around time
//  1               10              0               10
//  2               5               10              15
//  3               8               15              23
// Average waiting time = 8.333333
// Average turn around time = 16.000000