/**
 * File: water.c
 * -------------
 *
 * Prompts the user for the length of his or her shower in minutes (as a 
 * positive integer) and then prints the equivalent number of bottles of water.
 */


#include <cs50.h>
#include <stdio.h>


// The amount of water a shower uses per minute, measured in bottles of water.
#define BOTTLES_OF_WATER_USED_PER_MINUTE ( 12 )


int main(void)
{
	printf("minutes: ");
	int n_minutes = get_int();
	printf("bottles: %i\n", n_minutes*BOTTLES_OF_WATER_USED_PER_MINUTE);

	return 0;
}
