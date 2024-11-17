#include <stdio.h>

void roundRobin(int processes[], int n, int burst_time[], int quantum) {
    int remaining_time[n];
    int completion_time[n];
    int waiting_time[n];
    int turn_around_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        completion_time[i] = 0;
        waiting_time[i] = 0;
        turn_around_time[i] = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                flag = 1;
                if (remaining_time[i] <= quantum) {
                    current_time += remaining_time[i];
                    completion_time[i] = current_time;
                    remaining_time[i] = 0;
                    completed++;
                } else {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                }
            }
        }
        if (!flag)
            break;
    }

    // Calculate waiting time and turn around time
    for (int i = 0; i < n; i++) {
        turn_around_time[i] = completion_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
    }

    // Display results
    printf("Process\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i, burst_time[i], completion_time[i], waiting_time[i], turn_around_time[i]);
    }
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n]; // Burst time for each process
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        scanf("%d", &burst_time[i]);
    }

    int quantum; // Time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(NULL, n, burst_time, quantum);

    return 0;
}