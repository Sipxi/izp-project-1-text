#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // For isdigit()
#include <unistd.h>

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
}


bool findNumber(char *string, char characters[], int characters_length){
	int string_length = getStringLength(string);
	int matched_characters = 0;
	for (int i = 0; i < string_length; i++){
		for (int j = 0; j < characters_length; j++){
			if (string [i+j] == '+' && characters[j] == '0'){
				matched_characters++;
			}
			if (string[i + j] == characters[j]){
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

int findContacts(contact contacts[], int total_contacts, char *raw_input, contact found_contacts[]){
	int raw_input_length = getStringLength(raw_input);
	char *decoded_input[raw_input_length];
	int found_count = 0;
	decodeString(raw_input, decoded_input);
	for (int count = 0; count < total_contacts; count++){
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
	return found_count;
}
int main(int argc, char *argv[]){
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
		found_contacts_count = findContacts(contacts, total_contacts, raw_input, found_contacts);
		printContacts(found_contacts, found_contacts_count);
	}
	return EXIT_SUCCESS;
}
