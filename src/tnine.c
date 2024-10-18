#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // For isdigit()
#include <unistd.h>

// ? Try enum?
#define MAX_CHARACTERS_READ 100
#define MAX_CONTACT_INFO_LENGTH 100
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
	return -1;
}

// Based on floatingWindowSearch returns index of first occurance of character in string
// If not found, returns -1
int findCharOccurance(char *string, char characters_array[], int start_index){
	int found_index; // Initial value
	int characters_length = getStringLength(characters_array);
	for (int i = 0; i < characters_length; i++){
		found_index = floatingWindowSearch(string, start_index, getStringLength(string), characters_array[i]);
		if (found_index != -1){
			return found_index;
		}
	}	
	return -1;
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
	if (argc > 3){
		return NULL;
	}
	if (argc == 3){
		
		if (strcmp(argv[1], "-s" )){
	
			return NULL;
		}
		for (int i = 0; i < getStringLength(argv[2]); i++){
			if(!isdigit(argv[2][i])){

				return NULL;
			}
		}
		return argv[2];

	}
	if (argc == 2){
		for (int i = 0; i < getStringLength(argv[1]); i++){
			if(!isdigit(argv[1][i])){
				printf("Found not digit, returning");
				return NULL;
			}
		}
		return argv[1];
	}

	return NULL;
	/*
	if (argc == 2){
		for (int i = 0; i < getStringLength(argv[1]); i++){
			if(!isdigit(argv[1][i])){
				return NULL;
			}
		}
	}
	else{
		return NULL;
	}
	return argv[1];
	*/

}


bool findNumber(char *string, char characters[], int characters_length){
	int string_length = getStringLength(string);
	int matched_characters = 0;
	for (int i = 0; i < string_length; i++){
		for (int j = 0; j < characters_length; j++){
			if (string [i+j] == '+' && characters[j] == '0'){
				matched_characters++;
			}
			else if (string[i + j] == characters[j]){
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

bool findText(char *string, char *decoded_string[], int decoded_string_length){
	toLowerCase(string);
	int matched_characters;
	int char_found;
	int string_length = getStringLength(string);
	for (int str_idx = 0; str_idx < string_length; str_idx++){
		matched_characters = 0;

		for (int dec_str_idx = 0; dec_str_idx < decoded_string_length; dec_str_idx++){
			char_found = 0;

			for (int char_idx = 0; decoded_string[dec_str_idx][char_idx] != '\0'; char_idx++){
				if (string[str_idx + dec_str_idx] == decoded_string[dec_str_idx][char_idx]){
					char_found = 1;
					break;
				}
			}
			if (char_found){
				matched_characters++;
			}
			else{
				break;
			}
		}
		if (matched_characters == decoded_string_length){
			return true;
		}
	}
	return false;
}

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
void printContacts(contact contacts[], int count)
{
	if (count <= 0){
		printf("Not found");
		return;
	}
	for (int idx = 0; idx < count; idx++){
		if (contacts[idx].name[0] != '\0')
		{
			printf("%s, %s\n", contacts[idx].name, contacts[idx].number);
		}
		else{
			printf("Not found");
		}
	}
}

bool findTextS(char *string, char *characters[], int chararters_length){
	toLowerCase(string);
	int string_length = getStringLength(string);
	int found_index = 0;
	int match = 0;


	for (int i = 0; found_index < string_length; i++){
		found_index = findCharOccurance(string, characters[i], found_index);
		if(found_index == -1){
			return 0;
		}
		match++;
		found_index++;
		if (match == chararters_length){
			return 1;
		}
	}
	return 1;
}

bool findNumberS(char *string, char characters[]){
	toLowerCase(string);
	int string_length = getStringLength(string);
	int characters_length = getStringLength(characters);
	int found = 0;
	int match = 0;
	for (int i = 0; i < string_length; i++){
		found = floatingWindowSearch(string, found, string_length, characters[i]);
		if (found != -1){
			match++;
			found++;
		}
		else{
			return 0;
		}
		if (match == characters_length){
			return 1;
		}
	}
	return 0;
}


int findContacts(contact contacts[], int total_contacts, char *raw_input, contact found_contacts[], int mode){
	int raw_input_length = getStringLength(raw_input);
	char *decoded_input[raw_input_length];
	int found_count = 0;
	decodeString(raw_input, decoded_input);
	for (int count = 0; count < total_contacts; count++){
		if(mode == 3){
		if (findNumber(contacts[count].number, raw_input, raw_input_length)){
			found_contacts[found_count] = contacts[count];
			found_count++;
		}
		else{
			if (findText(contacts[count].name, decoded_input, raw_input_length)){
				found_contacts[found_count] = contacts[count];
				found_count++;
			}
		}
		}
		if(mode == 5){
			if (findNumberS(contacts[count].number, raw_input)){
			found_contacts[found_count] = contacts[count];
			found_count++;
		}
		else{
			if (findTextS(contacts[count].name, decoded_input, raw_input_length)){
				found_contacts[found_count] = contacts[count];
				found_count++;
			}
		}

		}
	}
	return found_count;
}



int main(int argc, char *argv[]){
	/*
	//char test_number[] = "123044312";
	char test_name[] = "xaxxxxbc";
	char *raw_input = parseUserInput(argc, argv);
	if (raw_input == NULL){
		fprintf(stderr, "Error: Invalid input.\n");
		return EXIT_ERROR;
	}
	int raw_input_length = getStringLength(raw_input);
	char *decoded_string[raw_input_length];
	decodeString(raw_input, decoded_string);
	int result;

	result = findContacts()
	printf("%d\n", result);
	*/



	
	
	contact contacts[MAX_CONTACT_INFO_LENGTH];
	contact found_contacts[MAX_CONTACT_INFO_LENGTH];
	int found_contacts_count = 0;
	int total_contacts = readContacts(contacts);
	if (total_contacts == EXCEEDED_MAX_LENGTH){
		fprintf(stderr, "Error: Input too long.\n");
		return EXIT_ERROR ;
	}


	if (argc <= 1){
		printContacts(contacts, total_contacts);
	}
	else{
		char *raw_input = parseUserInput(argc, argv);
		if (raw_input == NULL){
			fprintf(stderr, "Error: Invalid input.\n");
			return EXIT_ERROR;
		}
		if (argc == 3){
	
			found_contacts_count = findContacts(contacts, total_contacts, raw_input, found_contacts, 5);
			

		}
		else{
			found_contacts_count = findContacts(contacts, total_contacts, raw_input, found_contacts, 3);

		}
		printContacts(found_contacts, found_contacts_count);

	}
	
	
	return EXIT_SUCCESS;
}
