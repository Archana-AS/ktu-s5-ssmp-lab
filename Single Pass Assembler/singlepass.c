#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

struct input {
    char label[10], opcode[10], operand[10], mnemonic[5];
    int loc;
};

struct input table[MAX];

struct symtab {
    char sym[10];
    int f, val, ref;
};

struct symtab symtbl[MAX];

void main() {
    int f1, i = 1, j = 1, flag, locctr, x;
    char add[10], code[10], mnemcode[5];
    FILE *fp1, *fp2, *fp3;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("spout.txt", "w");

    fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    if (strcmp(table[i].opcode, "START") == 0) {
        locctr = atoi(table[i].operand);
        i++;
        fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    } else {
        locctr = 0;
    }
    while (strcmp(table[i].opcode, "END") != 0) {
        if (strcmp(table[i].label, "**") != 0) {
            // Check if the label already exists in the symbol table
            f1 = 0;
            for (x = 1; x < j; x++) {
                if (strcmp(symtbl[x].sym, table[i].label) == 0) {
                    f1 = 1; // Label already exists
                    break;
                }
            }
            if (f1 == 0) {
                // Add new label to symbol table
                strcpy(symtbl[j].sym, table[i].label);
                symtbl[j].val = locctr;
                symtbl[j].f = 0;
                j++;
            }
        }

        // Process opcode
        fscanf(fp2, "%s%s", code, mnemcode);
        while (strcmp(code, "END") != 0) {
            if (strcmp(table[i].opcode, code) == 0) {
                strcpy(table[i].mnemonic, mnemcode);
                locctr += 3; // Assuming all opcodes are of length 3
                for (x = 1; x < j; x++) {
                    flag = 0;
                    if (strcmp(table[i].operand, symtbl[x].sym) == 0) {
                        flag = 1;
                        if (symtbl[x].f == 0)
                            table[i].loc = symtbl[x].val;
                        break;
                    }
                }
                if (flag != 1 && strlen(table[i].operand) > 0) {
                    // Add operand to symbol table if it's not empty
                    strcpy(symtbl[j].sym, table[i].operand);
                    symtbl[j].f = 1;
                    symtbl[j].ref = i;
                    j++;
                }
            }
            fscanf(fp2, "%s%s", code, mnemcode);
        }
        rewind(fp2);
        // Handle directives
        if (strcmp(table[i].opcode, "WORD") == 0) {
            locctr += 3;
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = atoi(table[i].operand);
        } else if (strcmp(table[i].opcode, "RESW") == 0) {
            locctr += (3 * atoi(table[i].operand));
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = 0; // RESW does not have a location
        } else if (strcmp(table[i].opcode, "RESB") == 0) {
            locctr += atoi(table[i].operand);
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = 0; // RESB does not have a location
        } else if (strcmp(table[i].opcode, "BYTE") == 0) {
            ++locctr;
            if (table[i].operand[0] == 'C' || table[i].operand[0] == 'X') {
                // Handle character or hexadecimal byte
                table[i].loc = locctr; // Set location to current locctr
            } else {
                table[i].loc = locctr; // Set location to current locctr
            }
        }
        i++;
        fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    }

    // Output results
    for (x = 1; x <= i; x++) {
        fprintf(fp3, "%s\t%s\t%s\t%s\t%d\n", table[x].label, table[x].opcode, table[x].operand, table[x].mnemonic, table[x].loc);
    }
    for (x = 1; x < j; x++) {
        printf("%s\t%d\n", symtbl[x].sym, symtbl[x].val);
    }

    // Close files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}
