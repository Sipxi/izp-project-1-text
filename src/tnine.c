// Made by Serhij Čepil
// FIT VUT Student
// https://github.com/sipxi
// 10/10/2024

// The code is based on VUT FIT C Practicals
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* string_map[] ={
	"+", //0
	"",  // 1
	"abc", //2
	"def",// 3
	"ghi",// 4
	"jkl",// 5
	"mno",// 6
	"pqrs",// 7
	"tuv",// 8
	"wxyz"// 9

};


int getStringLength(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int floatingWindowSearch(char* string, int start_index, int end_index, char search_char){

	int found_index = -1;

	for (int i = start_index; i < end_index; i++){
		if (string[i] == search_char){
			found_index = i;
			printf("------------\n");
			printf("Found %c at index: %d\n", search_char, found_index);
			printf("Parametrs: %s, %d, %d, %c\n", string, start_index, end_index, search_char);
			printf("------------\n");
			break;
		}
	}
	return found_index;
}


/*
contact findContact(contact c, char* to_find){
	return c;
	

}


char* parseUserInput(int argc, char *argv[]){
	if (argc > 1){
		return argv[1];
	}
	return NULL;
}
*/

bool foundByCharArr(char* string, int length, char* characters){
	int start_index = 0;
	int end_index = length;
	int found_index;
	for (int i = 0; i < getStringLength(characters); i++){
		found_index = floatingWindowSearch(string, start_index, end_index, characters[i]);
		if(found_index == -1){
			return false;
			}
		else{
			start_index = found_index+1;
			}
	}
	return true;
}

int charToInt(char c){
	return c - '0';
	
}



int main() {
	char test_string[] = "petr dvorak";
	char test_char[] = "def";
	int string_length = getStringLength(test_string);
	bool result = foundByCharArr(test_string, string_length, test_char);

	printf("%d\n", result);

	

	return 0;
}


