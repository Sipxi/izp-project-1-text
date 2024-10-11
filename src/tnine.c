#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int getStringLength(char *str){
	int length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;
}
int charToInt(char c){
	return c - '0';
}
int floatingWindowSearch(char *string, int start_index, int end_index, char search_char){
	int found_index = -1;
	for (int i = start_index; i < end_index; i++)
	{
		if (string[i] == search_char)
		{
			found_index = i;
			break;
		}
	}
	return found_index;
}
void decodeString(char *string, char *decoded_string[]){
	int index = 0;
	while (string[index] != '\0')
	{
		int number = charToInt(string[index]);
		if (number >= 0 && number <= 9)
		{
			decoded_string[index] = string_map[number];
			//printf("%s", string_map[number]);
		}
		index++;
	}

}
char *parseUserInput(int argc, char *argv[]){
	// TODO Make it fucking better
	char *input;
	if (argc > 1)
	{
		input = argv[1];
	}
	else
	{
		return NULL;
	}

	return input;
}
bool foundByCharArr(char *string, int length, char *characters){
	int start_index = 0;
	int end_index = length;
	int found_index;
	for (int i = 0; i < getStringLength(characters); i++)
	{
		found_index = floatingWindowSearch(string, start_index, end_index, characters[i]);
		if (found_index == -1)
		{
			return false;
		}
		else
		{
			start_index = found_index + 1;
		}
	}
	return true;
}
bool testFind(char *string, int length, char *characters[], int chararters_length){
	int start_index = 0;
	int end_index = length;
	int found_index;
	int test_passed = 0;
	for (int i = 0; i < chararters_length; i++)
	{
		for (int j = 0; j < getStringLength(characters[i]); j++)
		{
			found_index = floatingWindowSearch(string, start_index, end_index, characters[i][j]);
			if (found_index != -1)
			{
				test_passed++;
				start_index = found_index + 1;
				printf("At least one of the characters was found\n");
				printf("Found character: %c\n", characters[i][j]);
				printf("Found index: %d\n", found_index);
				printf("Next start index: %d\n", start_index);
				break;
			}
		}
		if (found_index == -1 && test_passed == 0)
		{
			return false;
		}
		test_passed = 0;
	}
	return true;
}

int main(int argc, char *argv[])
{
	char *input = parseUserInput(argc, argv);
	int input_length = getStringLength(input);
	char *decoded_string[input_length];
	decodeString(input, decoded_string);

	for(int i = 0; i < getStringLength(input); i++){
		printf("{%s},", decoded_string[i]);
	}
	printf("\n");
	printf("Input length: %d\n", input_length);
	char test_string[] = "petr dvorak";
	int string_length = input_length;
	bool result = testFind(test_string, string_length, decoded_string, input_length);

	printf("Result is %s\n", result ? "true" : "false");
	/*char *test_set_of_chars[] = {"dev", "tuv"};
	int string_length = getStringLength(test_string);
	bool result = testFind(test_string, string_length, test_set_of_chars);
	*/

	return 0;
}
