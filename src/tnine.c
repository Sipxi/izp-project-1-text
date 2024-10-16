#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for isatty and fileno

#define MAX_CONTACT_INFO_LENGTH 100
#define INDEX_ERROR -1

// Maps strings to certain indexes
char *string_map[] = {
	"+",	// 0
	"",		// 1
	"abc",	// 2
	"def",	// 3
	"ghi",	// 4
	"jkl",	// 5
	"mno",	// 6
	"pqrs", // 7
	"tuv",	// 8
	"wxyz"	// 9
};

typedef struct {
	char name[MAX_CONTACT_INFO_LENGTH];
	char number[MAX_CONTACT_INFO_LENGTH];
} person;

typedef enum {
    NUMBER,
    TEXT
} MODE;


// TODO COMMENT
int charToInt(char input_character){
	return input_character - '0';
}



int getStringLength(char *string){
	printf("%s", string);
	int length = 0;
	while (string[length] != '\0'){
		length++;
	}
	return length;
}

void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A'); // Convert to lowercase
        }
    }
}


int floatingWindowSearch(char *string, int start_index, int end_index, char search_char){
	for (int index = start_index; index < end_index; index++){
		if (string[index] == search_char){
			return index;
		}
	}
	return INDEX_ERROR;
}

//Decodes string based on string_map, and stores it in decoded_string.
void decodeString(char *string, char *decoded_string[]){
	int index = 0;
	while (string[index] != '\0'){
		int number = charToInt(string[index]);
		if (number >= 0 && number <= 9){
			decoded_string[index] = string_map[number];
		}
		index++;
	}
}

// Parses user input, and returns only the first argument if it exists
char *parseUserInput(int argc, char *argv[]){
	return (argc > 1) ? argv[1] : NULL;
}

// Based on floatingWindowSearch returns index of first occurance of character in string
int findFirstCharOccurance(char *string, char characters_array[], int start_index){
	int found_index = -1;
	int characters_length = getStringLength(characters_array);
	for (int idx = 0; idx < characters_length; idx++){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string), characters_array[idx]);
		if (found_index != INDEX_ERROR){
			return found_index;
		}
	}	
	return INDEX_ERROR;
}



// Returns next index of character in string if it exists, otherwise returns INDEX_ERROR
int nextChar(char string[], char character, int start_index){
	printf("[IsNextChar] Character compared string %c to %c \n", string[start_index], character);
	printf("[IsNextChar] Returning index : %d\n", string[start_index] == character ? start_index + 1 : -1);
	return string[start_index] == character ? start_index + 1 : INDEX_ERROR; // start_index + 1 represents next index
	
}

// Returns next index of character_array in string if it exists, otherwise returns INDEX_ERROR
// TODO good naming of characters?
int isNextCharArray(char string[], char characters[], int start_index){
	printf("[IsNextCharArr] Start index is: %d\n", start_index);
	printf("[IsNextCharArr] got array: %s\n", characters);
	int characters_length = getStringLength(characters);
	int next_index = -1;
	for (int idx = 0; idx < characters_length; idx++){
		next_index = nextChar(string, characters[idx], start_index);
		if (next_index != INDEX_ERROR){
			return next_index;
		}

	}
	return INDEX_ERROR;
}

/** 
 * @brief Finds a pattern in a string or number in given string
 * 
 * So called generic function
 * based on mode, it calls the appropriate function to find the pattern
 * mode can be either TEXT or NUMBER
 * void *characters is later converted to char** or char* based on mode

*/
bool findPattern(char *string, void *characters, int characters_length, MODE mode){
	printf("Starting findPattern\n");
	toLowerCase(string);
	int start_index = 0;
	int found_index;

	if (mode == NUMBER){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string),((char *)characters)[0]);
	}
	else if (mode == TEXT){
		found_index = findFirstCharOccurance(string, ((char **)characters)[0], start_index);
	}
	if (found_index == INDEX_ERROR){
		return false;
	}
	int next_index = found_index +1;
	printf("-----------------\n");
	printf("In string: %s\n", string);
	printf("Found index: %d\n", found_index);
	if (mode == NUMBER){
		printf("Digit found: %c\n", string[found_index]);
	}
	else if (mode == TEXT){
		printf("Character found %c\n", string[found_index]);	
		
	}
	printf("First pattern found, continuing...\n");
	printf("Next index is: %d\n", next_index);
	printf("-----------------\n");

	for (int idx = 1; idx < characters_length; idx++){
		if (mode == NUMBER){
			next_index = nextChar(string, ((char *)characters)[idx], next_index);
		}
		else if (mode == TEXT){
			next_index = isNextCharArray(string, ((char **)characters)[idx], next_index);
		}
		if (next_index == INDEX_ERROR){
			return false;
		}
	}
	printf("-----------------\n");


	return found_index > INDEX_ERROR ? true : false;
}



int main(int argc, char *argv[]){
    person contacts[MAX_CONTACT_INFO_LENGTH]; // Array to hold contacts
    int count = 0; // Count of contacts read from stdin

    // Read data from stdin
    while (count < MAX_CONTACT_INFO_LENGTH && scanf("%s", contacts[count].number) == 1) {
        // Read the number first
        scanf(" %[^\n]", contacts[count].name); // Read the name
        count++;
    }

    // Print the contacts for verification
    for (int i = 0; i < count; i++) {
        printf("Person %d: Number: %s, Name: %s\n", i + 1, contacts[i].number, contacts[i].name);
    }

    // Print the contacts for verification
    printf("\n--- List of Contacts ---\n");
    for (int i = 0; i < count; i++) {
        printf("Contact %d: Number: %s, Name: %s\n", i + 1, contacts[i].number, contacts[i].name);
    }


	/*
	person testPerson;
	strcpy(testPerson.name, "Petr Novak");
	strcpy(testPerson.number, "0123456789");
	
	char *raw_input = parseUserInput(argc, argv);
	int raw_input_length = getStringLength(raw_input);
	int result = 0;

	char *decoded_string[raw_input_length];
	decodeString(raw_input, decoded_string);
	printf("-----------------\n");
	printf("Input String: %s\n", raw_input);
	printf("Input Length: %d\n", raw_input_length);
	printf("[");
	for (int idx = 0; idx < raw_input_length; idx++){
		printf(" {%s} ", decoded_string[idx]);
	}
	printf("]\n");
	printf("-----------------\n");

	result = findPattern(testPerson.number, raw_input, raw_input_length, NUMBER);

	if (!result){
		printf("No occurances found in number\n");
		result = findPattern(testPerson.name, decoded_string, raw_input_length, TEXT);
	}

	printf("result %d \n   ", result);
	*/
	
	return 0;
}

