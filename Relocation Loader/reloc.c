#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
  char add[6], length[10], input[10], binary[12], bitmask[12], relocbit;
  int start, inp, len, i, address, opcode, addr, actualadd;
  FILE * fp1, * fp2;
  printf("Enter the actual starting address: ");
  scanf("%d", & start);
  start -= 1000;
  fp1 = fopen("relinput.dat", "r");
  fp2 = fopen("reloutput.dat", "w");
  fscanf(fp1, "%s", input);
  while (strcmp(input, "E") != 0) {
    if (strcmp(input, "H") == 0)
      fscanf(fp1, "%s%s%s", add, length, input);
    if (strcmp(input, "T") == 0) {
      fscanf(fp1, "%d%s", & address, bitmask);
      address += start;
      len = strlen(bitmask);
      for (i = 0; i < len; i++) {
        fscanf(fp1, "%d%d", & opcode, & addr);
        relocbit = bitmask[i];
        if (relocbit == '0') actualadd = addr;
        else actualadd = addr + start;
        fprintf(fp2, "%d\t%d%d\n", address, opcode, actualadd);
        address += 3;
      }
      fscanf(fp1, "%s", input);
    }
  }
  fclose(fp1);
  fclose(fp2);
  printf("FINISHED\n");
}