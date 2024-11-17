#include<stdio.h>

#include<string.h>

#include<stdlib.h>

void main() {
  char a[10], ad[10], label[10], opcode[10], operand[10], mnemonic[10], symbol[10], start[10], t[200], t1[200], c1[10], a1[10];
  int i, address, code, add, len, actual_len, tlen = 0;
  FILE * fp1, * fp2, * fp3, * fp4, * fp5, * fp6;
  //strcpy(t,'');
  strcpy(t1, "");
  fp1 = fopen("assmlist.dat", "w");
  fp2 = fopen("symtab.dat", "r");
  fp3 = fopen("intermediate.dat", "r");
  fp4 = fopen("optab.dat", "r");
  fp5 = fopen("objrcd.dat", "w");
  fp6 = fopen("len.dat", "r");
  fscanf(fp3, "%s%s%s", label, opcode, operand);
  if (strcmp(opcode, "START") == 0) {
    fprintf(fp1, "\t%s\t%s\t%s\n", label, opcode, operand);
    strcpy(start, operand);
    fscanf(fp6, "%d", & len);
    fprintf(fp5, "H^%-6s^00%s^0000%d\nT^00%s^", label, operand, len, operand);
    fscanf(fp3, "%d%s%s%s", & address, label, opcode, operand);
    fclose(fp6);
  }
  while (strcmp(opcode, "END") != 0) {
    if (strcmp(opcode, "BYTE") == 0) {
      fprintf(fp1, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
      len = strlen(operand);
      actual_len = len - 3;
      for (i = 2; i < (actual_len + 2); i++) {
        sprintf(ad, "%X", operand[i]);
        fprintf(fp1, "%s", ad);
        if ((tlen + 2 * actual_len) <= 60) {
          //strcat(t,ad);
          strcat(t1, ad);
        } else {
          fprintf(fp5, "%x^%s", tlen / 2, t1);
          fprintf(fp5, "\nT^00%d", address);
          tlen = 0;
          //strcpy(t,'\0');
          strcpy(t1, "");
          //strcat(t,ad);
          strcat(t1, ad);
        }
      }
      fprintf(fp1, "\n");
      strcat(t1, "^");
      tlen += 2 * actual_len;
    } else if (strcmp(opcode, "WORD") == 0) {
      len = strlen(operand);
      sprintf(a, "%s", operand);
      fprintf(fp1, "%d\t%s\t%s\t%s\t00000%s\n", address, label, opcode, operand, a);
      if ((tlen + 6) <= 60) {
        //strcat(t,"0000");
        strcat(t1, "00000");
        //strcat(t,a);
        strcat(t1, a);
        strcat(t1, "^");
      } else {
        fprintf(fp5, "%x^%s", tlen / 2, t1);
        fprintf(fp5, "\nT^00%d", address);
        tlen = 0;
        //strcpy(t,'\0');
        strcpy(t1, "");
        //strcat(t,"0000");
        strcat(t1, "0000");
        //strcat(t,a);
        strcat(t1, a);
        strcat(t1, "^");
      }
      tlen += 6;
      //fprintf(fp5,"00000%s^",a);
    } else if ((strcmp(opcode, "RESB") == 0) || (strcmp(opcode, "RESW") == 0)) {
      fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);

    } else {
      rewind(fp4);
      fscanf(fp4, "%s%d", mnemonic, & code);
      while (strcmp(opcode, mnemonic) != 0)
        fscanf(fp4, "%s%d", mnemonic, & code);
      if (strcmp(operand, "**") == 0) {
        fprintf(fp1, "%d\t%s\t%s\t%s\t%d0000\n", address, label, opcode, operand, code);

      } else {
        rewind(fp2);
        fscanf(fp2, "%s%d", symbol, & add);
        while (strcmp(operand, symbol) != 0) {
          fscanf(fp2, "%s%d", symbol, & add);
        }
        fprintf(fp1, "%d\t%s\t%s\t%s\t%d%d\n", address, label, opcode, operand, code, add);
        //fprintf(fp5,"%d%d^",code,add);
        sprintf(c1, "%d", code);
        sprintf(a1, "%d", add);
        if ((tlen + 6) <= 60) {
          strcat(t1, c1);
          strcat(t1, a1);
          strcat(t1, "^");
        } else {
          fprintf(fp5, "%X^%s", tlen / 2, t1);
          fprintf(fp5, "\nT^00%d", address);
          tlen = 0;
          fprintf(fp5, "%s", t1);
          //strcpy(t,'\0');
          strcpy(t1, "");
          //strcat(t,c1);
          strcat(t1, a1);
          strcat(t1, "^");
        }
        tlen += 6;
      }
    }

    fscanf(fp3, "%d%s%s%s", & address, label, opcode, operand);
  }

  fprintf(fp5, "%X^%s", tlen / 2, t1);
  fprintf(fp1, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
  fprintf(fp5, "\nE^00%s", start);
  printf("\nFinished\n");
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  fclose(fp5);

}