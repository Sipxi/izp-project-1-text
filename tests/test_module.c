// Made by Serhij Čepil
// FIT VUT Student
// https://github.com/sipxi
// 09/10/2024

// The code is based on VUT FIT C Practicals


#include "test_case_manager.h"
#include <stdbool.h>
#include "../src/types.h"

// Function to test if a specific character is present in a string
TestValue test_contains_char(const char **inputs) {
    // Extract the string and the character from inputs
    char *string = (char *)inputs[0]; // The string to search in
    char target = inputs[1][0]; // The character to search for
    TestValue result;

    // Call the contains_char function and store the result as 1 for true, 0 for false
    result.int_val = contains_char(string, strlen(string), target) ? 1 : 0; 
    return result;
}


TestValue test_is_alpha(const char **inputs) {
    // Extract the character from inputs
    char c = inputs[0][0];

    TestValue result;

    result.int_val = is_alpha(c) ? 1 : 0;
    return result;
}

TestCase test_cases_is_alpha[] = {
    {
        "test is_alpha(lower)", 
        (const char *[]){ "a", NULL },
        { .int_val = 1 },
        TYPE_INT,
        test_is_alpha
    },
};


// Define test cases for contains_char
TestCase test_cases_contains_char[] = {
    // Test case where the character is present in the string
    {
        "Test contains_char (character present)",
        (const char *[]){ "hello", "h", NULL }, // Inputs: string, character to check
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT, // Expected type
        test_contains_char // Function to call
    },
    // Test case where the character is not present in the string
    {
        "Test contains_char (character not present)",
        (const char *[]){ "hello", "z", NULL },
        { .int_val = 0 }, // Expected result: false (0)
        TYPE_INT,
        test_contains_char
    },
    // Test case where the string is empty
    {
        "Test contains_char (empty string)",
        (const char *[]){ "", "a", NULL },
        { .int_val = 0 }, // Expected result: false (0)
        TYPE_INT,
        test_contains_char
    },
    // Test case where the character is a special character present in the string
    {
        "Test contains_char (special character present)",
        (const char *[]){ "hello, world!", "!", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    // Test case where the character is the first character in the string
    {
        "Test contains_char (character at start)",
        (const char *[]){ "test", "t", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    // Test case where the character is the last character in the string
    {
        "Test contains_char (character at end)",
        (const char *[]){ "test", "t", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
    // Test case where the character is present multiple times
    {
        "Test contains_char (character present multiple times)",
        (const char *[]){ "banana", "a", NULL },
        { .int_val = 1 }, // Expected result: true (1)
        TYPE_INT,
        test_contains_char
    },
};





// Main function to run the test suite for contains_char
int main() {
    // Run the defined test cases and calculate the results
    run_test_suite(test_cases_contains_char, sizeof(test_cases_contains_char) / sizeof(TestCase));
    run_test_suite(test_cases_is_alpha, sizeof(test_cases_is_alpha) / sizeof(TestCase));
    
    return 0; // Indicate successful execution
}
