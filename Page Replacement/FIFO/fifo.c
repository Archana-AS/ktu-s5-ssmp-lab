#include <stdio.h>

void main() {

  int i, j, n, f, in [20], pf = 0, k = 0, out[20];

  printf("Enter size of input string: ");
  scanf("%d", & n);

  printf("Enter the string elements\n");
  for (i = 0; i < n; i++) {
    scanf("%d", & in [i]);
  }

  printf("Enter the number of frames: ");
  scanf("%d", & f);
  for (j = 0; j < f; j++) {
    out[j] = -1;
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < f; j++) {
      if (out[j] == in [i]) {
        break;
      }
    }
    if (j == f) {
      out[k] = in [i];
      k++;
      pf++;
    }
    for (j = 0; j < f; j++) {
      printf("%d\t", out[j]);
    }
    printf("\ttotal page faults:%d\n", pf);
    if (k == f) {
      k = 0;
    }
  }
  printf("No. of page hits:%d\n", n - pf);
}