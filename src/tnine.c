#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef enum {
    NUMBER,
    TEXT
} MODE;

int charToInt(char c){
	return c - '0';
}

int getStringLength(char *string){
	int length = 0;
	while (string[length] != '\0'){
		length++;
	}
	return length;
}

int floatingWindowSearch(char *string, int start_index, int end_index, char search_char){
	for (int index = start_index; index < end_index; index++){
		if (string[index] == search_char){
			return index;
		}
	}
	return -1;
}

void decodeString(char *string, char *decoded_string[], MODE mode){
	int index = 0;
	if (mode == TEXT){
	while (string[index] != '\0'){
		int number = charToInt(string[index]);
		if (number >= 0 && number <= 9){
			decoded_string[index] = string_map[number];
		}
		index++;
	}
	} else if (mode == NUMBER){
		while (string[index] != '\0'){
			decoded_string[index] = string_map[index];
			index++;
		}
		
	}
}

char *parseUserInput(int argc, char *argv[]){
	return (argc > 1) ? argv[1] : NULL;
}



int findAtLeastOneChar(char *string, char characters[], int start_index){
	int found_index = -1;
	for (int i = 0; i < getStringLength(characters); i++){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string), characters[i]);
		if (found_index != -1){
			return found_index;
		}
	}	
	return -1;
}




int isNextChar(char string[], char character, int start_index){
	printf("[IsNextChar] Character compared string %c to %c \n", string[start_index], character);
	printf("[IsNextChar] Returning index : %d\n", string[start_index] == character ? start_index + 1 : -1);
	return string[start_index] == character ? start_index + 1 : -1;
	
}

int isNextCharArray(char string[], char characters[], int start_index){
	printf("[IsNextCharArr] Start index is: %d\n", start_index);
	printf("[IsNextCharArr] got array: %s\n", characters);
	int next_index = -1;
	for (int i = 0; i < getStringLength(characters); i++){
		next_index = isNextChar(string, characters[i], start_index);
		if (next_index != -1){
			return next_index;
		}

	}
	return -1;
}

/*
bool findNumber(char *string, char characters[], int chararters_length){
	printf("Entering findNumber\n");
	int start_index = 0;
	int found_index = floatingWindowSearch(string, start_index, getStringLength(string), characters[0]);
	int next_index = found_index +1;
	if (found_index == -1){
		return false;
	}
	printf("-----------------\n");
	printf("In number: %s\n", string);
	printf("Found index: %d\n", found_index);
	printf("Digit found %c\n", string[found_index]);
	printf("First digit found, continuing...\n");
	printf("Next index is: %d\n", next_index);
	printf("-----------------\n");

	for (int i = 1; i < chararters_length; i++){
		next_index = isNextChar(string, characters[i], next_index);
		if (next_index == -1){
			return false;
		}
	}
	return found_index > -1 ? true : false;
}

bool findText(char *string, char *characters[], int chararters_length){
	int start_index = 0;
	int found_index = findAtLeastOneChar(string, characters[0], start_index);
	int next_index = found_index +1;
	if (found_index == -1){
		return false;
	}
	printf("-----------------\n");
	printf("In string: %s\n", string);
	printf("Found index: %d\n", found_index);
	printf("Character found %c\n", string[found_index]);
	printf("In list {%s}\n", characters[0]);
	printf("First string found, continuing...\n");
	printf("Next index is: %d\n", next_index);
	printf("-----------------\n");

	for (int i = 1; i < chararters_length; i++){
		next_index = isNextCharArray(string, characters[i], next_index);
		if (next_index == -1){
			return false;
		}
	}
	printf("-----------------\n");

	return found_index > -1 ? true : false;
}
*/


bool findPattern(char *string, void *characters, int characters_length, MODE mode){
	printf("Starting findPattern\n");
	int start_index = 0;
	int found_index;

	if (mode == NUMBER){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string),((char *)characters)[0]);
	}
	else if (mode == TEXT){
		found_index = findAtLeastOneChar(string, ((char **)characters)[0], start_index);
	}
	if (found_index == -1){
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

	for (int i = 1; i < characters_length; i++){
		if (mode == NUMBER){
			next_index = isNextChar(string, ((char *)characters)[i], next_index);
		}
		else if (mode == TEXT){
			next_index = isNextCharArray(string, ((char **)characters)[i], next_index);
		}
		if (next_index == -1){
			return false;
		}
	}
	printf("-----------------\n");


	return found_index > -1 ? true : false;
}



int main(int argc, char *argv[]){
	char test_case[] = "petr dvorak";
	char test_number[] = "1234567890";
	char *raw_input = parseUserInput(argc, argv);
	int raw_input_length = getStringLength(raw_input);
	int result = 0;

	char *decoded_string[raw_input_length];
	decodeString(raw_input, decoded_string, TEXT);
	printf("-----------------\n");
	printf("Input String: %s\n", raw_input);
	printf("Input Length: %d\n", raw_input_length);
	printf("[");
	for (int i = 0; i < raw_input_length; i++){
		printf(" {%s} ", decoded_string[i]);
	}
	printf("]\n");
	printf("-----------------\n");

	result = findPattern(test_case, decoded_string, raw_input_length, TEXT);

	if (!result){
		printf("No occurances found in string\n");
		result = findPattern(test_number, raw_input, raw_input_length, NUMBER);
	}

	printf("result %d", result);
/*
	result = findText(test_case, decoded_string, raw_input_length);


	if (!result){
		printf("No occurances found in string\n");
		printf("Trying number..\n");
		result = findNumber(test_number, raw_input, raw_input_length);
	}

	printf("Result is %s\n", result ? "True" : "False");
	
*/

	return 0;
}

