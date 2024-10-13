// Made by Serhij Čepil
// FIT VUT Student
// https://github.com/sipxi
// 09/10/2024

// The code is based on VUT FIT C Practicals

#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct contact {
	char *name;
	char *number;
	
}contact;
bool test_find(char* string, int length, char* characters[]);
bool foundByCharArr(char* string, int length, char* characters);
bool findContact(char *contactInfo, char *characters[], int chararters_length);
int floatingWindowSearch(char* string, int start_index, int end_index, char search_char);
char* parseUserInput(int argc, char *argv[]);
int findFirstCharOccurance(char *string, char characters[], int start_index);

#endif
