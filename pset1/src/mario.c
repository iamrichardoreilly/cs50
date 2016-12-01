/**
 * File: mario.c
 * -------------
 *
 * Recreates the "half-pyramid" of blocks that Mario must ascend toward the end 
 * of World 1-1 in Nintendo's Super Mario Brothers.
 * Uses hashes (#) for blocks.
 */


#include <cs50.h>
#include <stdio.h>


// The half-pyramid's height must be a non-negative integer no greater than 23.
#define PYRAMID_H_MIN ( 0 )
#define PYRAMID_H_MAX ( 23 )


int main(void)
{

	// Prompt the user for the half-pyramid's height.
	int pyramid_h;
	do
	{
		printf("Height: ");
		pyramid_h = get_int();
	}
	while (pyramid_h < PYRAMID_H_MIN || pyramid_h > PYRAMID_H_MAX);

	// Draw the half-pyramid.
	for (int row = 0; row < pyramid_h; row++)
	{
		for (int col = 0, n_blocks = row + 2; col <= pyramid_h; col++)
		{
			printf("%c", (col <= pyramid_h - n_blocks) ? ' ' : '#');
		}
		printf("\n");
	}

	return 0;
}
