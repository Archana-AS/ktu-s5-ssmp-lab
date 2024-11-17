#include <stdio.h>
void  main() {
  int pid[15], bt[15], at[15], n, tat[15],wt[15],ct[15],i;
  printf("Enter the number of processes: ");
  scanf("%d", & n);

  printf("Enter process id of all the processes: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", & pid[i]);
  }

  printf("Enter arrival time of all the processes: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", & at[i]);
  }

  printf("Enter burst time of all the processes: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", & bt[i]);
  }

  // Sort processes based on arrival time
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (at[j] > at[j + 1]) {
        // Swap process ID
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
  ct[0] = at[0] + bt[0];
  for (i = 1; i < n; i++) {
    ct[i] = ct[i - 1] + bt[i];
  }

  tat[0] = ct[0] - at[0];
  for (i = 1; i < n; i++) {
    tat[i] = ct[i] - at[i];
  }

  wt[0] = 0;
  for (i = 1; i < n; i++) {
    wt[i] = tat[i] - bt[i];
  }

  printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
  for (i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
  }

  float Avgtat = 0;
  float Avgwt = 0;
  for (i = 0; i < n; i++) {
    Avgtat += tat[i];
    Avgwt += wt[i];
  }
  Avgtat = Avgtat / n;
  Avgwt = Avgwt / n;
  printf("Average Turnaround Time: %f\n", Avgtat);
  printf("Average Waiting Time: %f\n", Avgwt);
}