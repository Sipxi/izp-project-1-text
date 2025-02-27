# FIT VUT Basics of Programming Project 1 - Text Processing: T9 Predictive Search 📱🔍

## Overview 🌟
This project focuses on creating a simplified algorithm to search contacts in a phonebook based on a sequence of digits entered by the user. The goal is to emulate the T9 predictive text system, where each digit corresponds to multiple characters. The user enters a sequence of digits, and the program searches for contacts whose names or phone numbers contain a sequence of characters matching the input digits.

## Objective 🎯
The aim of this project is to implement a program that:
- Takes a sequence of digits as input.
- Searches for contacts whose name or phone number contains the corresponding characters for the entered sequence.
- Outputs a list of matching contacts or states that no contacts were found.

## Key Requirements 📝
- **Input**: A sequence of digits (0-9) representing a search query.
- **Output**: A list of contacts that match the given criteria. The contact information is printed as "Name, Phone Number".

### Search Criteria 🔢
- The program must find **consecutive subsequences** of characters represented by the digits. 
    - For example, the digit `2` represents `a`, `b`, `c`; the digit `3` represents `d`, `e`, `f`; and so on.
    - The program should match the given digit sequence with characters in the name or phone number, treating the sequence as a pattern.

### Example Input/Output 💬

#### Sample Phonebook (`seznam.txt`):


#### Commands and Outputs:
1. **Search with no filter**:
    ```bash
    ./tnine < seznam.txt
    ```
    Output:
    ```
    petr dvorak, 603123456
    jana novotna, 777987654
    bedrich smetana ml., 541141120
    ```

2. **Search with filter `12`**:
    ```bash
    ./tnine 12 < seznam.txt
    ```
    Output:
    ```
    petr dvorak, 603123456
    bedrich smetana ml., 541141120
    ```

3. **Search with filter `686`**:
    ```bash
    ./tnine 686 < seznam.txt
    ```
    Output:
    ```
    jana novotna, 777987654
    ```

4. **Search with no matches (`111`)**:
    ```bash
    ./tnine 111 < seznam.txt
    ```
    Output:
    ```
    Not found
    ```

## Constraints 🚫
- **Memory Management**: No use of dynamic memory allocation (e.g., `malloc`/`free`).
- **File Handling**: The program should only work with standard input/output (`stdin`, `stdout`).
- **Sorting**: Do not use built-in sorting functions like `qsort`, `lsearch`, or `bsearch`.

## Development Environment ⚙️
- **Language**: C (C11 standard)
- **Compilation**: Use the following command to compile:
  ```bash
  gcc -std=c11 -Wall -Wextra -Werror tnine.c -o tnine
  ```
## Error Handling ⚠️

The program should handle the following error scenarios gracefully:

1. **Invalid Input Format**:
   - If the input is not a valid sequence of digits (0-9) or if the contact list format is incorrect, the program should output an error message and terminate.
   - Example: 
     - Invalid sequence input: `Invalid input! Please provide a valid numeric filter.`
     - Invalid contact format: `Invalid contact format! A contact must contain both a name and a phone number.`

2. **Empty Phonebook or Missing Contact Info**:
   - If the phonebook is empty or contains contacts with missing names or phone numbers, the program should display a relevant error message and exit.
   - Example: `Phonebook is empty or contains invalid data.`

3. **File Read/Write Errors**:
   - The program should gracefully handle any issues while reading input from `stdin`. If an error occurs, an appropriate message should be displayed.
   - Example: `Error reading input! Could not process the contact list.`

4. **No Contacts Found**:
   - If no contacts match the search criteria, the program should display the message `Not found` and exit without crashing.
   - Example: If no contact matches the sequence `111`, the program should print: `Not found`.

5. **Invalid Filter Input**:
   - If the user enters an invalid filter (e.g., letters or special characters instead of digits), the program should immediately display an error and exit.
   - Example: `Invalid filter! Please provide a sequence of digits only.`

6. **Unexpected Runtime Errors**:
   - The program should handle unexpected errors during execution, such as memory issues or invalid data processing, by printing a generic error message and exiting.
   - Example: `Unexpected error! Exiting program.`

7. **Buffer Overflow or Memory Issues**:
   - If the input exceeds the buffer limit (e.g., a line longer than 100 characters), the program should detect this and output an error message indicating the problem.
   - Example: `Input line too long! Maximum line length is 100 characters.`

8. **Invalid Command Usage**:
   - If the user runs the program without arguments or with incorrect arguments, the program should output a usage message and exit.
   - Example: `Usage: ./tnine <CISLO> < contact_list.txt` or `Usage: ./tnine -s <CISLO> < contact_list.txt` if `-s` flag is used for partial sequence search.

9. **Invalid Character Encoding**:
   - The program should be robust against invalid character encoding or non-ASCII characters in the input file. If it encounters non-ASCII characters, it should print an error message and terminate.
   - Example: `Invalid character encoding detected! Only ASCII characters are supported.`

The program should not crash under any circumstances but should exit gracefully with an appropriate message if any of the above errors occur. The error messages should be clear, concise, and helpful in understanding what went wrong.







  
