# CS 3503 Assignment 1 – Number Base Conversion

## Author
Carlos Mata

## Description
My implementation of a number base conversion utility.  
This project includes:
- `div_convert`: converts integers to a given base using division/remainder
- `sub_convert`: converts integers to a given base using subtraction of powers
- `print_tables`: demonstrates binary, octal, decimal, and hex output, plus bitwise operations (shift and mask)

## Build Instructions

As a MacOS user, I used command lines directly in my terminal to run my program. 

```bash

gcc -Wall -Wextra -pedantic -o convert main.c convert.c
./convert > output.txt

## Test Results

Below is an excerpt from `output.txt`:

```text
Test: div_convert (156, 8) -> Expected: "234", Got: "234" [PASS]
Test: div_convert (255, 16) -> Expected: "FF", Got: "FF" [PASS]
Test: sub_convert (42, 16) -> Expected: "2A", Got: "2A" [PASS]
Test: sub_convert (4294967295, 2) -> Expected: "11111111111111111111111111111111", Got: "11111111111111111111111111111111" [PASS]

Summary: 99/99 tests passed

## Notes

This was my first time working with C. Although the syntax felt somewhat similar to Java, which I have more experience in, the project still brought challenges that I wasn’t expecting.  

One of the biggest adjustments was understanding data types like `uint32_t`. Since C is closer to a "talk to the metal" language, concepts such as signed vs. unsigned integers and fixed-width integer types were new to me. I had to research how these work, and especially how they behave at their limits (for example: uint32_t` max value = 4,294,967,295).  

The first issue I ran into was simply opening and reading the test file. At first, my program couldn’t find it, and the fix turned out to be just moving the test file into my project folder. However, debugging this problem taught me more about how C handles file operations like opening, reading, and closing files. This is an area I didn't have to much experience in so I am glad I was able to be exposed to this. 

Even after I could read the file, I wasn’t sure what to do with the contents. I learned that "reading a file" in C only loads the text into memory, but I still needed to tell the program how to interpret it. This led me to research and eventually understand what tokenizing is. Tokenizing is where the program breaks each line into parts (like function name, number, base, expected output). This took a lot of trial and error, but it eventually started working.  

Later, when I ran my program in the terminal, it seemed to get “stuck”. It would print a few results and then stop. I assumed the issue was in my `main.c` loops, so I spent hours inserting debug lines. To my surprise, the bug was actually in my `convert.c` file, specifically in the `sub_convert` method.  

Originally, my method for finding the largest power of the base used multiplication. But with large values, multiplying pushed the number over the `uint32_t` limit, which caused it to “wrap around” to 0. This locked the loop into an infinite cycle. After researching, I discovered a safer way: instead of multiplying first, I used division to check whether the next multiplication would overflow. This fixed the problem and taught me a valuable lesson about overflow in C.  

Overall, this project gave me hands-on practice with file I/O, string parsing, base conversion algorithms, and the quirks of C’s fixed-width integer types. It was frustrating at times, but each bug I hit pushed me to learn more and get a deeper understanding of the language.
