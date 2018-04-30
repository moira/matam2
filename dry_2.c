#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* RemoveFirstAppearance(char* string, char* word);

//I'm so not sure that it is what they really wanted
//At least, there are no memory leaks

int main () {
	//simple case
	char* test1 = RemoveFirstAppearance("abc", "ab");
	printf ("remove ab from abc: %s\n", test1);
	//the word is empty
	char* test2 = RemoveFirstAppearance("ma", "");
	printf ("remove '' from ma: %s\n", test2);
	//the string is empty
	char* test3 = RemoveFirstAppearance("", "ma");
	printf ("remove ma from '': %s\n", test3);
	//the string is shorter than the word
	char* test4 = RemoveFirstAppearance("ma", "mamama");
	printf ("remove mamama from ma: %s\n", test4);
	//there are 0 occurrences of the word in the string
	char* test5 = RemoveFirstAppearance("abbc", "abc");
	printf ("remove abc from abbc: %s\n", test5);
	//there is more than one occurrence of the word in the string
	char* test6 = RemoveFirstAppearance("RabRab", "ab");
	printf ("remove ab from RabRab: %s\n", test6);
	//overlapping substrings
	char* test7 = RemoveFirstAppearance("ababa", "aba");
	printf ("remove aba from ababa: %s\n", test7);
	//identical strings
	char* test8 = RemoveFirstAppearance("ababa", "ababa");
	printf ("remove ababa from ababa: %s\n", test8);
	free(test1);
	free(test2);
	free(test3);
	free(test4);
	free(test5);
	free(test6);
	free(test7);
	return 0;
}

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
			return NULL; //?????
		}
		memcpy(ReducedString, string, substring-string);
		memcpy(ReducedString+(substring-string), "\0", 1);
    	strcat(ReducedString, substring+strlen(word));
		return ReducedString;
	}
}
