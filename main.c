#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Course: CS 3053 - Comp Org & Arch
// Assignment: A1 - Data Representation
// Language: C Programming
// Topics: Number bases, bit manipulation
// Version: 2.0 (Fixed)
// Carlos Mata - Main

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main(void) {
    FILE *file = fopen("a1_test_file.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char line[256];
    int total = 0;
    int passed = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // normalize line endings
        line[strcspn(line, "\n")] = '\0';
        size_t L = strlen(line);
        if (L && line[L-1] == '\r') line[L-1] = '\0';

        // trim left and skip blanks/comments
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0' || *p == '#') continue;

        // individualize the words so algo knows what to do
        char *cmd = strtok(p, " \t");
        if (!cmd) continue;

        if (strcmp(cmd, "div_convert") == 0 || strcmp(cmd, "sub_convert") == 0) {
            char *n_str    = strtok(NULL, " \t");
            char *base_str = strtok(NULL, " \t");
            char *expected = strtok(NULL, " \t");
            if (!n_str || !base_str || !expected) {
                printf("Error parsing line\n");
                continue;
            }

            uint32_t n = (uint32_t)strtoul(n_str, NULL, 10);
            int base   = (int)strtol(base_str, NULL, 10);

            char got[65];
            if (cmd[0] == 'd') div_convert(n, base, got);
            else               sub_convert(n, base, got);

            int ok = (strcmp(got, expected) == 0);
            printf("Test: %s (%u, %d) -> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   cmd, n, base, expected, got, ok ? "PASS" : "FAIL");
            total++;
            if (ok) passed++;
        }
        else if (strcmp(cmd, "print_tables") == 0) {
            char *n_str = strtok(NULL, " \t");
            if (!n_str) { printf("Malformed print_tables line\n"); continue; }
            uint32_t n = (uint32_t)strtoul(n_str, NULL, 10);
            print_tables(n);
            printf("Test: print_tables (%u) [FORMATTED OUTPUT]\n", n);
            total++;
            passed++;  // counting as pass if it printed successfully
        }
        else {
            printf("Unknown command: %s\n", cmd);
        }
    }

    fclose(file);
    printf("Summary: %d/%d tests passed\n", passed, total);
    return 0;
}
