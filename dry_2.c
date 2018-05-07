#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* RemoveFirstAppearance(char* string, char* word);

int main () {
	//simple case
	char* test = RemoveFirstAppearance("abc", "ab");
	printf ("remove ab from abc: %s\n", test);
	free(test);
	//the word is empty
	test = RemoveFirstAppearance("ma", "");
	printf ("remove '' from ma: %s\n", test);
	free(test);
	//the string is empty
	test = RemoveFirstAppearance("", "ma");
	printf ("remove ma from '': %s\n", test);
	free(test);
	//the string is shorter than the word
	test = RemoveFirstAppearance("ma", "mamama");
	printf ("remove mamama from ma: %s\n", test);
	free(test);
	//there are 0 occurrences of the word in the string
	test = RemoveFirstAppearance("abbc", "abc");
	printf ("remove abc from abbc: %s\n", test);
	free(test);
	//there is more than one occurrence of the word in the string
	test = RemoveFirstAppearance("RabRab", "ab");
	printf ("remove ab from RabRab: %s\n", test);
	free(test);
	//overlapping substrings
	test = RemoveFirstAppearance("ababa", "aba");
	printf ("remove aba from ababa: %s\n", test);
	free(test);
	//identical strings
	test = RemoveFirstAppearance("ababa", "ababa");
	printf ("remove ababa from ababa: %s\n", test);
	free(test);
	return 0;
}

/*Removes the first appearance of one sequence of characters (word)
  from another (string), returns the reduced string.
  If the string is shorter than the word,
  or the word is not met with in the string,
  or memory allocation has failed, –
  returns null.*/
char* RemoveFirstAppearance(char* string, char* word) {
	if (string == NULL || word == NULL) {
		return NULL;
	}
	char* substring = strstr(string, word);
	if (substring == NULL) {
		return NULL;
	} else {
		char* ReducedString = malloc(strlen(string)-strlen(word)+1);
		if (ReducedString == NULL) {
			return NULL;
		}
		memcpy(ReducedString, string, substring-string);
		memcpy(ReducedString+(substring-string), "\0", 1);
		strcat(ReducedString, substring+strlen(word));
		return ReducedString;
	}
}
