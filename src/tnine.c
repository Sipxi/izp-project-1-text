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
} Mode;

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

void decodeString(char *string, char *decoded_string[], Mode mode){
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

bool findContact(char *contactInfo, char *characters[], int chararters_length){
	int found_index = -1;
	int start_index = 0;
	for (int i = 0; i < chararters_length; i++){
		found_index = findAtLeastOneChar(contactInfo, characters[i], start_index);
		if (found_index == -1){
			return false;
		}
		found_index++;
		start_index = found_index;
	}
	return found_index > -1 ? true : false;
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


bool findNumber(char *string, char characters[], int chararters_length){
	int start_index = 0;
	int found_index = -1;
	int character_length = getStringLength(string);
	for (int i = 0; i < chararters_length; i++){
		found_index = floatingWindowSearch(string, start_index, character_length, characters[i]);
		if (found_index == -1){
			return false;
		}
		found_index++;
		start_index = found_index;

	}
	return found_index > -1 ? true : false;
	
}





int main(int argc, char *argv[]){

	char test_number[] = "0123456789";
	//char test_case[] = "petr dvorak";
	bool result;
	char *raw_input = parseUserInput(argc, argv);

	int raw_input_length = getStringLength(raw_input);
	result = findNumber(test_number, raw_input,raw_input_length);

	printf("%d\n", result);


	/*
	char *decoded_string[raw_input_length];
	decodeString(raw_input, decoded_string);
	printf("Input String: %s\n", raw_input);
	printf("Input Length: %d\n", raw_input_length);
	printf("[");
	for (int i = 0; i < raw_input_length; i++){
		printf(" {%s} ", decoded_string[i]);
	}
	printf("]\n");
	

	
	printf("Result: %d\n", result);
	*/
	return 0;
}

