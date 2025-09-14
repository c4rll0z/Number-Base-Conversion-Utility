#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Course: CS 3053 - Comp Org & Arch
// Assignment: A1 - Data Representation
// Language: C Programming
// Topics: Number bases, bit manipulation
// Version: 2.0 (Fixed)
// Carlos Mata - Convert

//div convert method
void div_convert(uint32_t n, int base, char *out) {
    char temp[65];  //temp buffer
    int pos = 0;

    //handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    //extract digits from right to left
    while (n > 0) {
        int remainder = n % base;
        n = n/base;

        // convert digit to character
        if (remainder < 10)
            temp[pos++] = '0' + remainder;
        else
            temp[pos++] = 'A' + (remainder - 10);
    }

    // reverse the result
    // TODO: Your code here!

    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - 1 - i]; //copies in reverse the elements from temp to out
    }
    out[pos] = '\0'; //terminator (not the movie)
}

//sub convert method
void sub_convert(uint32_t n, int base, char *out) {
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    uint32_t power = 1;\
    // had to change the below method to divide first, getting overflow errors (int will wraparound to 0)
    while (power <= n / (uint32_t)base) {
        power *= (uint32_t)base;
    }

    while (power > 0) {
        int remainder = n / power;

        // convert digit to character
        if (remainder < 10)
            out[pos++] = '0' + remainder;
        else
            out[pos++] = 'A' + (remainder - 10);

        n -= remainder * power;
        power /= base;
    }

    out[pos] = '\0'; //terminator 2 (good movie)
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    //original number
    div_convert (n , 2 , bin ) ;
    div_convert (n , 8 , oct ) ;
    div_convert (n , 16 , hex ) ;
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n" ,bin ,oct, n, hex);

    //left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n" ,bin ,oct, shifted, hex);

    //AND with 0xff
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n" ,bin ,oct, masked, hex);
}
