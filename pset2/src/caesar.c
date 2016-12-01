/**
 * File: caesar.c
 * --------------
 *
 * Usage: ./caesar k
 *
 * Encrypts messages using Caesar's cipher.
 * Prompts the user for a string of plaintext and then outputs that text with 
 * each alphabetical character "rotated" by k positions; non-alphabetical 
 * characters are outputted unchanged.
 */


#include <cs50.h>
#include <ctype.h>
#include <stdio.h>


#define N_CHARACTERS_IN_ALPHABET ( 26 )


int main(int argc, char **argv)
{

	// Ensure correct usage.
	if (argc != 2)
	{
		printf("Usage: ./caesar k\n");

		return 1;
	}

	// Ensure k is valid.
	int c = 0;
	while (argv[1][c] != '\0')
	{
		if (!isdigit(argv[1][c]))
		{
			printf("k must be a non-negative integer\n");

			return 1;
		}

		c++;
	}
	int k = atoi(argv[1]);

	// Prompt user for a message.
	string p = get_string();

	// Output encrypted message.
	c = 0;
	k%=N_CHARACTERS_IN_ALPHABET;
	char min_c, max_c;
	while (p[c] != '\0')
	{
		if (isalpha(p[c]))
		{
			if (isupper(p[c]))
			{
				min_c = 'A';
				max_c = 'Z';
			}
			else
			{
				min_c = 'a';
				max_c = 'z';
			}

			printf("%c", (p[c] + k <= max_c) ? p[c] + k : min_c + (p[c] + k - max_c - 1));
		}
		else
		{
			printf("%c", p[c]);
		}

		c++;
	}
	printf("\n");

	return 0;
}
