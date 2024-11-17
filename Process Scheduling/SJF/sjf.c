#include <stdio.h>

#include <stdbool.h>

void main() {
  int pid[15];
  int bt[15];
  int at[15];
  int n;
  int tat[15];
  int wt[15];
  int ct[15];
  int executed[15]

  printf("Enter number of processes\n");
  scanf("%d", & n);

  printf("Enter process ids\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", & pid[i]);
  }

  printf("Enter arrival time\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", & at[i]);
  }

  printf("Enter burst time\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", & bt[i]);
  }
  for (int i = 0; i < n; i++) {
    executed[i] = false;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (at[j] > at[j + 1]) {

        int temp = pid[j];
        pid[j] = pid[j + 1];
        pid[j + 1] = temp;

        temp = at[j];
        at[j] = at[j + 1];
        at[j + 1] = temp;

        temp = bt[j];
        bt[j] = bt[j + 1];
        bt[j + 1] = temp;
      }
    }
  }
  int currentTime = 0;
  int completedProcesses = 0;

  currentTime += bt[0];
  ct[0] = currentTime;
  tat[0] = ct[0] - at[0];
  wt[0] = tat[0] - bt[0];
  executed[0] = true;
  completedProcesses++;

  while (completedProcesses < n) {
    int nextProcessIndex = -1;

    for (int i = 0; i < n; i++) {
      if (!executed[i] && at[i] <= currentTime) {
        if (nextProcessIndex == -1 || bt[i] < bt[nextProcessIndex]) {
          nextProcessIndex = i;
        }
      }
    }

    // If no process has arrived yet, increment the current time
    if (nextProcessIndex == -1) {
      currentTime++;
      continue;
    }

    // Execute the process with the smallest burst time
    currentTime += bt[nextProcessIndex];
    ct[nextProcessIndex] = currentTime;
    tat[nextProcessIndex] = ct[nextProcessIndex] - at[nextProcessIndex];
    wt[nextProcessIndex] = tat[nextProcessIndex] - bt[nextProcessIndex];
    executed[nextProcessIndex] = true;
    completedProcesses++;
  }

  printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
  }

  float Avgtat = 0;
  float Avgwt = 0;
  for (int i = 0; i < n; i++) {
    Avgtat += tat[i];
    Avgwt += wt[i];
  }
  Avgtat = Avgtat / n;
  Avgwt = Avgwt / n;
  printf("Average Turnaround Time: %f\n", Avgtat);
  printf("Average Waiting Time: %f\n", Avgwt);

}