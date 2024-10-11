# Test Case Framework

This test framework is designed to facilitate the creation and execution of unit tests for various functions in C. 
It supports different data types, including **integers, floats, doubles, and strings**. 
This framework allows you to define test cases that include the function to test, its inputs, the expected output, and the data type of the output.

## Contents

- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Files](#files)
- [Contributing](#contributing)
- [License](#license)


## Overview

- **Purpose:** A lightweight testing framework to execute unit tests for various functions.
- **Supported Types:** Integer, Float, Double, String.
- **Output:** Detailed results with emoji indicators for pass or fail.

## Installation

To use the test framework, simply clone the repository.

## Files

- **`test_framework.h`**: Header file containing definitions for the framework, including types, enums, and function declarations.
- **`test_module.c`**: Example usage of the framework, including a test function and predefined test cases.

## `test_framework.h`


### Includes

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

### Enums and Data Structures
`TestType` **Enum**

Represents the different types of data that the test framework supports:

```c
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
} TestType;

```

`TestValue` **Union**

The union holds different type of values:


```c
typedef union {
    int int_val;
    float float_val;
    double double_val;
    const char* str_val;
} TestValue;

```
`TestFunc` **Typedef**

Defines a function pointer type for the test functions:
```c
typedef TestValue (*TestFunc)(const char **);


```

`TestCase` **Struct**

Represents an individual test case:
```c
typedef struct {
    const char *name;       // Name of the test case
    const char **inputs;    // Array of inputs for the test case
    TestValue expected;     // Expected result for the test case
    TestType type;          // Type of the expected and actual result
    TestFunc func;          // Pointer to the test function
} TestCase;


```

## `test_module.c`

This file defines the test cases and a test function for specific functionalities.

### Includes

```
#include "test_framework.h"
#include <stdbool.h>
#include "../src/types.h"

```
## Example Test Function

The following function tests if a specific character is present in a string:

```c

TestValue test_contains_char(const char **inputs) {
    // Extract the string and the character from inputs
    char *string = (char *)inputs[0]; // The string to search in
    char target = inputs[1][0]; // The character to search for
    TestValue result;

    // Call the contains_char function and store the result as 1 for true, 0 for false
    result.int_val = contains_char(string, strlen(string), target) ? 1 : 0; 
    return result;
}


```

## Test Cases


 set of test cases is defined using `TestCase` structs:

```c
 TestCase test_cases_contains_char[] = {
    {
        "Test contains_char (character present)",
        (const char *[]){ "hello", "h", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT, // Expected type
        test_contains_char // Function to call
    },
    {
        "Test contains_char (character not present)",
        (const char *[]){ "hello", "z", NULL },
        { .int_val = 0 }, // Expected result: false (0)
        TYPE_INT,
        test_contains_char
    },
    {
        "Test contains_char (empty string)",
        (const char *[]){ "", "a", NULL },
        { .int_val = 0 }, // Expected result: false (0)
        TYPE_INT,
        test_contains_char
    },
    {
        "Test contains_char (special character present)",
        (const char *[]){ "hello, world!", "!", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    {
        "Test contains_char (character at start)",
        (const char *[]){ "test", "t", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    {
        "Test contains_char (character at end)",
        (const char *[]){ "test", "t", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    {
        "Test contains_char (character present multiple times)",
        (const char *[]){ "banana", "a", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
};
```

## Main Function

The `main` function runs all the defined test cases:

```

int main() {
    // Run the defined test cases and calculate the results
    run_test_suite(test_cases_contains_char, sizeof(test_cases_contains_char) / sizeof(TestCase));
    
    return 0; // Indicate successful execution
}

```


## Usage

1. **Define a Test Function:** Write a function that accepts a set of string inputs and returns a `TestValue`.
2. **Create Test Cases:** Use the `TestCase` struct to define the function to test, inputs, expected output, and data type.
3. **Run the Test Suite:** Call `run_test_suite()` with an array of `TestCase` and the number of test cases.


## Example Usage

```c

TestValue test_example_function(const char **inputs) {
    // Custom logic for testing
}

TestCase example_test_cases[] = {
    { "Example Test", (const char *[]){"input1", "input2", NULL}, { .int_val = 1 }, TYPE_INT, test_example_function }
};

int main() {
    run_test_suite(example_test_cases, sizeof(example_test_cases) / sizeof(TestCase));
    return 0;
}


```

### Makefile

By default I made a fully functional make file
**DON'T FORGET TO CHANGE YOUR COMPILER!**

#### `make all`

Compiles EVERYTHING

#### `make main`

Just compiles main

#### `make test`

Compiles test module

#### `make clean`

Deletes .exe that were generated by Compiler



## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue to discuss any improvements or bugs.

## License

This project is licensed under the MIT License - see the LICENSE file for details.



