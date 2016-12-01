/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

typedef struct node
{
	struct node *children[27];  // 26 letters (a-z) plus apostrophe.
	bool is_word;
}
node;

node *root_node;

size_t dictionary_size = 0;

void unload_rec(node *current_node);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	int i = 0;
	node *current_node;
	while (word[i] != '\0')
	{
		if (!i)
		{
			current_node = root_node;
		}

		int char_index = (word[i] == '\'') ? 26 : tolower(word[i]) - 'a';
		if (!current_node->children[char_index])
		{
			return false;
		}
		current_node = current_node->children[char_index];

		i++;
	}

	return current_node->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	FILE *fp = fopen(dictionary, "r");
	if (!fp)
	{
		printf("Could not open %s.\n", dictionary);

		return false;
	}

	root_node = malloc(sizeof(node));

	// Load each word in dictionary.
	int index = 0;
	char word[LENGTH + 1];
	for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
	{

		// Allow only alphabetical characters and apostrophes.
		if (isalpha(c) || (c == '\'' && index > 0))
		{

			// Append character to word.
			word[index] = c;
			index++;

			// Ignore alphabetical strings too long to be words.
			if (index > LENGTH)
			{

				// Consume remainder of alphabetical string.
				while ((c = fgetc(fp)) != EOF && isalpha(c));

				// Prepare for new word.
				index = 0;
			}
		}

		// Ignore words with numbers (like MS Word can).
		else if (isdigit(c))
		{

			// Consume remainder of alphanumeric string.
			while ((c = fgetc(fp)) != EOF && isalnum(c));

			// Prepare for new word.
			index = 0;
		}

		// We must have found a new word.
		else if (index > 0)
		{

			// Terminate current word.
			word[index] = '\0';

			int i = 0;
			node *current_node, *next_node;
			while (word[i] != '\0')
			{
				if (!i)
				{
					current_node = root_node;
				}

				int char_index = (word[i] == '\'') ? 26 : word[i] - 'a';
				if (!current_node->children[char_index])
				{
					next_node = malloc(sizeof(node));
					current_node->children[char_index] = next_node;
				}
				else
				{
					next_node = current_node->children[char_index];
				}
				current_node = next_node;

				i++;
			}
			current_node->is_word = true;

			dictionary_size++;

			// Prepare for new word.
			index = 0;
		}
	}

	// Check whether there was an error.
	if (ferror(fp))
	{
		fclose(fp);
		printf("Error reading %s.\n", dictionary);

		return false;
	}

	fclose(fp);

	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
	return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	unload_rec(root_node);
	return true;
}

void unload_rec(node *current_node)
{
	for (int i = 0; i < 27; i++)
	{
		if (current_node->children[i])
		{
			unload_rec(current_node->children[i]);
		}
	}
	free(current_node);
}
