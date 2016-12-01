/**
 * File: initials.c
 * ----------------
 *
 * Prompts the user for their name and then outputs their initials in uppercase 
 * with no spaces or periods.
 * Assumes that the user's input will contain only letters (uppercase and/or 
 * lowercase) plus single letters between words.
 */


#include <cs50.h>
#include <ctype.h>
#include <stdio.h>


int main(void)
{

	// Prompt the user for their name.
	string name = get_string();

	// Print user's initials in uppercase.
	int c = 0;
	while (name[c] != '\0')
	{
		if (!c || name[c - 1] == ' ')
		{
			printf("%c", toupper(name[c]));
		}

		c++;
	}
	printf("\n");

	return 0;
}
