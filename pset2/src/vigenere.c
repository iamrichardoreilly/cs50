/**
 * File: vigenere.c
 * ----------------
 *
 * Usage: ./vigenere k
 *
 * Encrypts messages using Vigenère's cipher.
 */


#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{

	// Ensure correct usage.
	if (argc != 2)
	{
		printf("Usage: ./vigenere k\n");

		return 1;
	}

	// Ensure k is valid.
	int c = 0;
	while (argv[1][c] != '\0')
	{
		if (!isalpha(argv[1][c]))
		{
			printf("k must be composed entirely of alphabetical characters\n");

			return 1;
		}

		c++;
	}
	string k = argv[1];

	// Prompt user for a message.
	string p = get_string();

	// Output encrypted message.
	c = 0;
	int k_index = 0, encrypt_by;
	char min_c, max_c;
	while (p[c] != '\0')
	{

		// Loop back to the start of k if we have already used every character 
		// in k to encrypt.
		if (k_index == strlen(k))
		{
			k_index = 0;
		}

		// Treat A and a as 0, B and b as 1, ..., and Z and z as 25.
		encrypt_by = toupper(k[k_index]) - 'A';

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

			printf("%c", (p[c] + encrypt_by <= max_c) ? 
					p[c] + encrypt_by : 
					min_c + (p[c] + encrypt_by - max_c - 1));

			k_index++;
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
