// Made by Serhij Čepil
// FIT VUT Student
// https://github.com/sipxi
// 09/10/2024

// The code is based on VUT FIT C Practicals

#ifndef TEST_CASE_MANAGER_H
#define TEST_CASE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum to represent different data types
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
} TestType;

// Union to hold different types of values
typedef union {
    int int_val;
    float float_val;
    double double_val;
    const char* str_val;
} TestValue;

// Define a type for test functions that return TestValue and accept multiple inputs
typedef TestValue (*TestFunc)(const char **);

// Define a structure to hold individual test case information
typedef struct {
    const char *name;       // Name of the test case
    const char **inputs;    // Array of inputs for the test case
    TestValue expected;     // Expected result for the test case
    TestType type;          // Type of the expected and actual result
    TestFunc func;          // Pointer to the test function
} TestCase;

// Function to compare two TestValue based on TestType
int compare_values(TestValue expected, TestValue actual, TestType type) {
    switch (type) {
        case TYPE_INT:
            return expected.int_val == actual.int_val;
        case TYPE_FLOAT:
            return expected.float_val == actual.float_val;
        case TYPE_DOUBLE:
            return expected.double_val == actual.double_val;
        case TYPE_STRING:
            return strcmp(expected.str_val, actual.str_val) == 0;
        default:
            fprintf(stderr, "Unsupported type for comparison\n");
            return 0; // Unsupported type
    }
}

// Function to print a TestValue based on TestType
void print_test_value(TestValue value, TestType type, char *buffer, size_t buffer_size) {
    switch (type) {
        case TYPE_INT:
            snprintf(buffer, buffer_size, "%d", value.int_val);
            break;
        case TYPE_FLOAT:
            snprintf(buffer, buffer_size, "%.2f", value.float_val);
            break;
        case TYPE_DOUBLE:
            snprintf(buffer, buffer_size, "%.2lf", value.double_val);
            break;
        case TYPE_STRING:
            snprintf(buffer, buffer_size, "\"%s\"", value.str_val);
            break;
        default:
            snprintf(buffer, buffer_size, "Unsupported Type");
    }
}

// Function to print the test result with emoji and test details
void print_result(int iteration, const char *test_name, const char **inputs, 
                  TestType type, TestValue expected, TestValue actual) {
    char input_buffer[256] = {0}; // Buffer for formatted inputs

    // Format the inputs into a single string
    for (size_t i = 0; inputs[i] != NULL; i++) {
        if (i > 0) {
            strncat(input_buffer, ", ", sizeof(input_buffer) - strlen(input_buffer) - 1); // Add a comma separator safely
        }
        strncat(input_buffer, inputs[i], sizeof(input_buffer) - strlen(input_buffer) - 1); // Append the input safely
    }

    // Buffers for expected and actual values as strings
    char expected_str[64], actual_str[64];
    print_test_value(expected, type, expected_str, sizeof(expected_str));
    print_test_value(actual, type, actual_str, sizeof(actual_str));

    // Compare expected and actual values
    int pass = compare_values(expected, actual, type);

    // Print the result
    printf("Test: %d %s: %s(test: %s) expected %s, got %s\n", 
           iteration, pass ? "✅ PASS" : "❌ FAIL", test_name, input_buffer, expected_str, actual_str);
}

// Function to run a single test case
int run_test_case(TestCase *test_case, int iteration) {
    TestValue actual = test_case->func(test_case->inputs); // Call the test function
    print_result(iteration, test_case->name, test_case->inputs, 
                 test_case->type, test_case->expected, actual);
    return compare_values(test_case->expected, actual, test_case->type) ? 0 : 1; // Return 0 for pass, 1 for fail
}

// Function to run a test suite and report results
void run_test_suite(TestCase *tests, size_t test_count) {
    int total_passed = 0; // Count of tests that passed
    int total_failed = 0; // Count of tests that failed

    printf("🎉 Running Tests...\n");
    printf("──────────────────────────────────────────\n");

    for (size_t i = 0; i < test_count; i++) {
        int result = run_test_case(&tests[i], i + 1); // Call the test function

        if (result == 0) {
            total_passed++;
        } else {
            total_failed++;
        }
    }

    // Summary of the test results
    printf("──────────────────────────────────────────\n");
    printf("Total tests passed: %d\n", total_passed);
    printf("Total tests failed: %d\n", total_failed);
    printf("🎉 All tests completed!\n");
}

#endif // TEST_CASE_MANAGER_H
