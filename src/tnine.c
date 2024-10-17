#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ? Try enum?
#define MAX_CHARACTERS_READ 100
#define MAX_CONTACT_INFO_LENGTH 99
#define EXCEEDED_MAX_LENGTH -2
#define INDEX_ERROR -1
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0

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

typedef struct{
	char name[MAX_CONTACT_INFO_LENGTH];
	char number[MAX_CONTACT_INFO_LENGTH];
} contact;

typedef enum{
	NUMBER,
	TEXT
} MODE;

// TODO COMMENT
// TODO UNSAFE
// TODO check if it's digit
int charToInt(char input_character){
	return input_character - '0';
}

int getStringLength(char *string){
	int length = 0;
	while (string[length] != '\0'){
		length++;
	}
	return length;
}

void toLowerCase(char *string){
	for (int chr_index = 0; string[chr_index] != '\0'; chr_index++){
		if (string[chr_index] >= 'A' && string[chr_index] <= 'Z'){
			string[chr_index] += ('a' - 'A');
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

// Decodes string based on string_map, and stores it in decoded_string.
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
	int found_index = INDEX_ERROR;
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
	printf("[IsNextChar] Character compared string %c to characters %c \n", string[start_index], character);
	printf("[IsNextChar] Returning index : %d\n", string[start_index] == character ? start_index + 1 : INDEX_ERROR);
	return string[start_index] == character ? start_index + 1 : INDEX_ERROR; // start_index + 1 represents next index
}

// Returns next index of character_array in string if it exists, otherwise returns INDEX_ERROR
// TODO good naming of characters?
int isNextCharArray(char string[], char characters[], int start_index){
	printf("[IsNextCharArr] Start index is: %d\n", start_index);
	printf("[IsNextCharArr] got array: %s\n", characters);
	int characters_length = getStringLength(characters);
	int next_index = INDEX_ERROR;
	for (int idx = 0; idx < characters_length; idx++){
		next_index = nextChar(string, characters[idx], start_index);
		if (next_index != INDEX_ERROR){
			return next_index;
		}
	}
	return INDEX_ERROR;
}



bool findNumber(char *string, char characters[], int characters_length) {
	printf("[FindNumber] In string: %s\n", string);
	printf("[FindNumber] In list {%s}\n", characters);
	int string_length = getStringLength(string);
	int matched_characters = 0;
	for (int i = 0; i < string_length; i++){
		for (int j = 0; j < characters_length; j++){
			if (string[i+j] == characters[j]){
				matched_characters++;
			}
		}
		if (matched_characters == characters_length){
			return true;
		}
		matched_characters = 0;

	}
	return false;

}

bool findText(char *string, char *characters[], int chararters_length){
	toLowerCase(string);
	int start_index = 0;
	int found_index = findFirstCharOccurance(string, characters[0], start_index);
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
			found_index = findFirstCharOccurance(string, characters[0], found_index+1);
		}
	}
	printf("-----------------\n");

	return found_index > -1 ? true : false;
}





/**
 * @brief Finds a pattern in a string or number in given string
 *
 * So called generic function
 * based on mode, it calls the appropriate function to find the pattern
 * mode can be either TEXT or NUMBER
 * void *characters is later converted to char** or char* based on mode
 * ! MORE THEN ONE OCCURRENCE OF CHARACTER IS NOT SUPPORTED
 * TODO Add support for more then one occurence
*/
/*
bool findPattern(char *string, void *characters, int characters_length, MODE mode){
	printf("Starting findPattern\n");
	toLowerCase(string);
	int start_index = 0;
	int found_index;

	if (mode == NUMBER){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string), ((char *)characters)[0]);
	}
	else if (mode == TEXT){
		found_index = findFirstCharOccurance(string, ((char **)characters)[0], start_index);
	}
	if (found_index == INDEX_ERROR){
		return false;
	}
	int next_index = found_index + 1;
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
*/


// Function to read contacts
// TODO MAX CONTACT check if it works
int readContacts(contact contacts[])
{
	int count = 0;
	while (count < MAX_CONTACT_INFO_LENGTH){
		if (fgets(contacts[count].name, MAX_CHARACTERS_READ, stdin) == NULL){
			return count; // END OF FILE, return count of contacts read
		}
		contacts[count].name[strcspn(contacts[count].name, "\n")] = '\0'; // Remove newline character

		if (getStringLength(contacts[count].name) >= MAX_CONTACT_INFO_LENGTH){
			return EXCEEDED_MAX_LENGTH; // Name too long, return error code
		}
		fgets(contacts[count].number, MAX_CHARACTERS_READ, stdin);

		contacts[count].number[strcspn(contacts[count].number, "\n")] = '\0'; // Remove newline character

		if (getStringLength(contacts[count].number) >= MAX_CONTACT_INFO_LENGTH){
			return EXCEEDED_MAX_LENGTH; // Number too long, return error code
		}
		count++;
	}
	return count;
}

// Function to print contacts
void printContacts(contact contacts[], int count){
	if (count <= 0){
		printf("No contacts found!\n");
		return;
	}
	printf("\n--- List of Contacts ---\n");
	for (int idx = 0; idx < count; idx++){
		if(contacts[idx].name[0] != '\0'){
			printf("Contact %d: Number: %s Name: %s\n", idx + 1, contacts[idx].number, contacts[idx].name);
		}
	}
	printf("-----------------\n");
}

void findContacts(contact contacts[], int total_contacts, char *raw_input, contact found_contacts[]){
	int raw_input_length = getStringLength(raw_input);
	char *decoded_input[raw_input_length];
	decodeString(raw_input, decoded_input);

	for (int idx = 0; idx < raw_input_length; idx++){
		//printf(" {%s} \n", decoded_input[idx]);
	}

	for (int count = 0; count < total_contacts; count++){
		if (findNumber(contacts[count].number, raw_input, raw_input_length)){
			found_contacts[count] = contacts[count];
		}
		else{
			if (findText(contacts[count].name, decoded_input, raw_input_length)){
				found_contacts[count] = contacts[count];
			}
		}
	}
}
int main(int argc, char *argv[])
{
	/*
	contact contacts[MAX_CONTACT_INFO_LENGTH];
	contact found_contacts[MAX_CONTACT_INFO_LENGTH];

	int total_contacts = readContacts(contacts);
	if (total_contacts == EXCEEDED_MAX_LENGTH)
	{
		printf("Error: Name or number is too long\n");
		return EXIT_ERROR;
	}
	printContacts(contacts, total_contacts);

	if (argc <= 1)
	{
		printContacts(contacts, total_contacts);
	}
	else
	{
		char *raw_input = parseUserInput(argc, argv);
		findContacts(contacts, total_contacts, raw_input, found_contacts);
		printContacts(found_contacts, total_contacts);
	}
		*/


	contact testPerson;
	strcpy(testPerson.name, "pddr DVorak");
	strcpy(testPerson.number, "541141120");

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

	//result = findNumber(testPerson.number, raw_input, raw_input_length);
	result = findText(testPerson.name, decoded_string, raw_input_length);
	printf("result %d \n   ", result);

	/*
	if (!result){
		printf("No occurances found in number\n");
		result = findText(testPerson.name, decoded_string, raw_input_length);
	}
	


	printf("result %d \n   ", result);
	*/
	


	return EXIT_SUCCESS;
}
