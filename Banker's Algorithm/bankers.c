#include <stdio.h>

#include <stdlib.h>

void main() {
  int n, m, i, available[10], j, max[10][10], allocated[10][10], need[10][10], finish[10];

  int flag, y = 0, fin[70], l, k;

  printf("Enter the number of processes: ");
  scanf("%d", & n);

  printf("Enter the number of resources: ");
  scanf("%d", & m);

  printf("Enter available number of instance for each resources \n");
  for (i = 0; i < m; i++) {
    printf("Resource%d : ", i + 1);
    scanf("%d", & n);
  }

  printf("Enter max resource count  for each process\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("process%d - resource%d : ", i + 1, j + 1);
      scanf("%d", & max[i][j]);
    }
  }

  printf("Enter allocated resource count  for each process\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("process%d - resource%d : ", i + 1, j + 1);
      scanf("%d", & allocated[i][j]);
    }
  }

  printf("Need matrix\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      need[i][j] = max[i][j] - allocated[i][j];
      printf("%d  ", need[i][j]);
    }
    printf("\n");
  }

  for (i = 0; i < n; i++) finish[i] = 0;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < n; j++) {

      if (finish[j] == 0) {

        flag = 0;
        for (k = 0; k < m; k++) {

          if (need[j][k] > available[k]) {
            flag = 1;
            break;
          }
        }

        if (flag == 0) {
          fin[y++] = j;
          for (l = 0; l < m; l++) {
            available[l] += allocated[j][l];
          }
          finish[j] = 1;
        }
      }
    }
  }

  for (i = 0; i < n; i++) {
    if (finish[i] == 0) {
      printf("Not safe state");
      exit(1);
    }
  }

  printf("System is in safe state\n");
  for (i = 0; i < n - 1; i++) {
    printf("P%d-> ", fin[i]);
  }
  printf("P%d ", fin[n - 1]);
}