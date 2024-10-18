// Made by Serhij Čepil
// FIT VUT Student
// https://github.com/sipxi
// Day of completion 09/18/2024
// Time spent: 19h+

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

typedef enum MODE{
	NORMAL_MODE = 0,
	S_MODE = 1,
}MODE;

int charToInt(char input_character){
	// If character is digit then convert to int, if not return INDEX_ERROR
	return (isdigit(input_character) ? input_character - '0' : INDEX_ERROR);
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

int floatingWindowSearch(char* string, int start_index, int end_index, char search_char){
	int found_index = -1;
	for (int idx = start_index; idx < end_index; idx++){
		if (string[idx] == search_char){
			found_index = idx;
			break;
		}
	}
	return found_index;
}

int findMin(int array[], int array_length){
	if (array_length == 0){
		return -1;
	}
	int min_int = array[0]; // Take first element as min
	for (int number_idx = 1; number_idx < array_length; number_idx++){
		if (array[number_idx] < min_int){
			min_int = array[number_idx];
		}
	}
	return min_int;
}

// Based on floatingWindowSearch returns index of first occurance of character in string
// If not found, returns -1
int findFirstCharOccurance(char *string, char characters_array[], int start_index){
	int found_index;
	int string_length = getStringLength(string);
	int characters_length = getStringLength(characters_array);
	int min_index_found = -1;
	for (int idx = 0; idx < characters_length; idx++){
		found_index = floatingWindowSearch(string, start_index, string_length, characters_array[idx]);
		if (found_index != -1 && (min_index_found == -1 || (min_index_found > found_index) )){
			min_index_found = found_index;
		}
	}
	return min_index_found;
}

// Helper function to check if all characters in string are digits
bool isAllDigits(char *string){
	for (int digit_idx = 0; digit_idx < getStringLength(string); digit_idx++){
		if (!isdigit(string[digit_idx])){
			return false;
		}
	}
	return true;
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
		if (strcmp(argv[1], "-s" ) != 0 || !isAllDigits(argv[2])){
			return NULL;
		}
		return argv[2];
	}
	if (argc == 2 && isAllDigits(argv[1])){
		return argv[1];
		}
	return NULL;
}

bool findNumber(char *string, char characters[], int characters_length){
	int string_length = getStringLength(string);
	int matched_characters = 0;

	for (int substring_start_idx = 0; substring_start_idx < string_length; substring_start_idx++){
		for (int chr_idx = 0; chr_idx < characters_length; chr_idx++){
			// Just to match + as well
			if (string [substring_start_idx+chr_idx] == '+' && characters[chr_idx] == '0'){
				matched_characters++;
			}
			//	Default algorithm to find substring
			else if (string[substring_start_idx + chr_idx] == characters[chr_idx]){
				matched_characters++;
			}
		}
		// If all characters are matched then return true
		if (matched_characters == characters_length){
			return true;
		}
		// Reset matched_characters if not every character needed is matched
		matched_characters = 0;
	}
	return false;
}

// The same algorithm as findNumber but n^3 complexity? Three nested loops
bool findText(char *string, char *decoded_string[], int decoded_string_length){
	toLowerCase(string); // Convert it to lower case

	int matched_characters;
	int char_found;
	int string_length = getStringLength(string);

	for (int str_idx = 0; str_idx < string_length; str_idx++){
		matched_characters = 0; // Reset matched counter

		for (int dec_str_idx = 0; dec_str_idx < decoded_string_length; dec_str_idx++){

			char_found = false; // Reset character found flag
			for (int char_idx = 0; decoded_string[dec_str_idx][char_idx] != '\0'; char_idx++){
				if (string[str_idx + dec_str_idx] == decoded_string[dec_str_idx][char_idx]){
					// If character from decoded string array is found, set to true and break out of inner loop
					char_found = true;
					break;
				}
			}
			// If flag char_found is true, increment matched counter, try next dec_array
			if (char_found){
				matched_characters++;
			}
			else{
				break;
			}
		}
		// If all characters are matched then return true
		if (matched_characters == decoded_string_length){
			return true;
		}
	}
	return false;
}

int readContacts(contact contacts[])
{
	int count = 0;
	while (count < MAX_CONTACT_INFO_LENGTH){
		if (fgets(contacts[count].name, MAX_CHARACTERS_READ, stdin) == NULL){
			return count; // END OF FILE, return count of contacts read
		}
		contacts[count].name[strcspn(contacts[count].name, "\n")] = '\0';	// Change newline character to null

		if (getStringLength(contacts[count].name) >= MAX_CONTACT_INFO_LENGTH){
			return EXCEEDED_MAX_LENGTH;	// Name too long, return error code
		}
		fgets(contacts[count].number, MAX_CHARACTERS_READ, stdin);

		contacts[count].number[strcspn(contacts[count].number, "\n")] = '\0'; 

		if (getStringLength(contacts[count].number) >= MAX_CONTACT_INFO_LENGTH){
			return EXCEEDED_MAX_LENGTH;	// Number too long, return error code
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
	int found_index = 0;

	for(int chr_idx = 0; chr_idx < chararters_length; chr_idx++){
		found_index = findFirstCharOccurance(string, characters[chr_idx], found_index);
		if (found_index == -1){
			return false;
		}
		found_index++;
	}
	return true;
}

bool findNumberS(char *string, char characters[]){
	int string_length = getStringLength(string);
	int characters_length = getStringLength(characters);
	int found_index = 0;

	for (int chr_idx = 0; chr_idx < characters_length; chr_idx++){
		found_index = floatingWindowSearch(string, found_index, string_length, characters[chr_idx]);
		if (found_index == -1){
			return false;
		}
		found_index++;
	}
	return true;
}

int findContacts(contact contacts[], int total_contacts, char *raw_input, contact found_contacts[], MODE mode){
	int raw_input_length = getStringLength(raw_input);
	char *decoded_input[raw_input_length];
	int found_count = 0;
	decodeString(raw_input, decoded_input);
	for (int count = 0; count < total_contacts; count++){
		if (mode == NORMAL_MODE){
			if (findNumber(contacts[count].number, raw_input, raw_input_length) || 
				findText(contacts[count].name, decoded_input, raw_input_length)){
				found_contacts[found_count] = contacts[count];
				found_count++;
				}
			}
		if (mode == S_MODE){
			if (findNumberS(contacts[count].number, raw_input) || 
				findTextS(contacts[count].name, decoded_input, raw_input_length)){
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
	MODE mode;

	int total_contacts = readContacts(contacts);
	if (total_contacts == EXCEEDED_MAX_LENGTH){
		fprintf(stderr, "[EXIT ERROR] Exceeded max input length\n");
		return EXIT_ERROR ;
	}
	if (argc <= 1){
		printContacts(contacts, total_contacts);
		return EXIT_SUCCESS;
	}
	char *raw_input = parseUserInput(argc, argv);
	if (raw_input == NULL){
		fprintf(stderr, "[EXIT ERROR] Invalid input\n");
		return EXIT_ERROR;
	}
	mode = argc == 3 ? S_MODE : NORMAL_MODE;

	int found_contacts_count = findContacts(contacts, total_contacts, raw_input, found_contacts, mode);
	printContacts(found_contacts, found_contacts_count);
	return EXIT_SUCCESS;
}
