# FIT VUT Basics of Programming Project 1 - Text Processing: T9 Predictive Search 📱🔍
# Mark: 9.67/10


## Overview 🌟
This project focuses on creating a simplified algorithm to search contacts in a phonebook based on a sequence of digits entered by the user. The goal is to emulate the T9 predictive text system, where each digit corresponds to multiple characters. The user enters a sequence of digits, and the program searches for contacts whose names or phone numbers contain a sequence of characters matching the input digits.

## Objective 🎯
The aim of this project is to implement a program that:
- Takes a sequence of digits as input.
- Searches for contacts whose name or phone number contains the corresponding characters for the entered sequence.
- Outputs a list of matching contacts or states that no contacts were found.

## Usage 📜

### Command Syntax

The program can be executed using the following syntax:
    ```bash
    ./tnine CISLO < contact_list.txt
    ```
    - **CISLO**: The sequence of digits (0-9) representing the search criteria. Each digit corresponds to a set of possible characters (e.g., 2 → `a, b, c`, 3 → `d, e, f`).
    - **contact_list.txt**: A text file containing the phonebook data. Each contact should consist of two non-empty lines: the name and the phone number.

#### Example 1: Basic Search

To search for contacts using the sequence `12` (which corresponds to `a, b, c` for `1` and `d, e, f` for `2`), you can run:
```bash
./tnine 12 < contact_list.txt

```
This will print all contacts whose name or phone number contains a substring matching the given sequence of digits.

#### Example 2: Search with No Matches

If the sequence `111` does not match any contact in the phonebook, the program will display:
```
Not found
```


#### Example 3: Search with a Partial Sequence (Optional `-s` Flag)

If you want to enable a partial sequence search (where characters from the sequence may be separated by any other characters), use the `-s` flag:
```bash
./tnine -s 38 < contact_list.txt
```







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

## Error Handling ⚠️

The program should handle the following error scenarios gracefully:

1. **Invalid Input Format**:
   - If the input is not a valid sequence of digits (0-9) or if the contact list format is incorrect, the program should output an error message and terminate.

2. **Empty Phonebook or Missing Contact Info**:
   - If the phonebook is empty or contains contacts with missing names or phone numbers, the program should display a relevant error message and exit.

3. **File Read/Write Errors**:
   - The program should gracefully handle any issues while reading input from `stdin`. If an error occurs, an appropriate message should be displayed.

4. **No Contacts Found**:
   - If no contacts match the search criteria, the program should display the message `Not found` and exit without crashing.

5. **Invalid Filter Input**:
   - If the user enters an invalid filter (e.g., letters or special characters instead of digits), the program should immediately display an error and exit.

7. **Buffer Overflow or Memory Issues**:
   - If the input exceeds the buffer limit (e.g., a line longer than 100 characters), the program should detect this and output an error message indicating the problem.

8. **Invalid Command Usage**:
   - If the user runs the program without arguments or with incorrect arguments, the program should output a usage message and exit.
   - Example: `Usage: ./tnine <CISLO> < contact_list.txt` or `Usage: ./tnine -s <CISLO> < contact_list.txt` if `-s` flag is used for partial sequence search.


The program should not crash under any circumstances but should exit gracefully with an appropriate message if any of the above errors occur. The error messages should be clear, concise, and helpful in understanding what went wrong.

## Development Environment ⚙️
- **Language**: C (C11 standard)
- **Compilation**: Use the following command to compile:
  ```bash
  gcc -std=c11 -Wall -Wextra -Werror tnine.c -o tnine
  ```







  
