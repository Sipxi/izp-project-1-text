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

char *parseUserInput(int argc, char *argv[]){
	return (argc > 1) ? argv[1] : NULL;
}

bool findName(char *string, char *characters[], int chararters_length){
	int start_index = 0;
	int found_index = -1;
	int end_index = getStringLength(string);
	for (int i = 0; i < chararters_length; i++){
		for (int j = 0; j < getStringLength(characters[i]); j++){
			found_index = floatingWindowSearch(string, start_index, end_index, characters[i][j]);
			if (found_index != -1){
				start_index = found_index +1;
				break;
			}
		}
		if (found_index == -1){
			return false;
		}
	}
	return found_index > -1 ? true : false;
}


int main(int argc, char *argv[]){
	char test_case[] = "petr dvorak";
	char *input = parseUserInput(argc, argv);
	int input_length = getStringLength(input);
	char *decoded_string[input_length];
	decodeString(input, decoded_string);

	printf("Input String: %s\n", input);
	printf("Input Length: %d\n", input_length);
	printf("[");
	for (int i = 0; i < input_length; i++){
		printf(" {%s} ", decoded_string[i]);
	}
	printf("]\n");

	bool result = findName(test_case, decoded_string, input_length);
	printf("Result: %d\n", result);

	return 0;
}

