/**
 * File: greedy.c
 * --------------
 *
 * Asks the user how much change is owed and then prints out the minimum 
 * number of coins with which said change can be made.
 */


#include <cs50.h>
#include <math.h>
#include <stdio.h>


#define CENTS_IN_A_DOLLAR ( 100 )

// Coins available.
#define QUARTER ( 25 )
#define DIME ( 10 )
#define NICKEL ( 5 )
#define PENNY ( 1 )


int main(void)
{

	// Prompt the user for change owed.
	printf("O hai! How much change is owed?\n");
	float change_owed_dollars = get_float();
	while (change_owed_dollars < 0)
	{
		printf("How much change is owed?\n");
		change_owed_dollars = get_float();
	}

	// Convert change owed from dollars to cents.
	int change_owed_cents = round(change_owed_dollars*CENTS_IN_A_DOLLAR);

	// Compute and print the minimum number of coins with which change can be 
	// made.
	int min_coins_needed_to_make_change = 0;
	while (change_owed_cents)
	{
		if (change_owed_cents >= QUARTER)
		{
			change_owed_cents-=QUARTER;
		}
		else if (change_owed_cents >= DIME)
		{
			change_owed_cents-=DIME;
		}
		else if (change_owed_cents >= NICKEL)
		{
			change_owed_cents-=NICKEL;
		}
		else
		{
			change_owed_cents-=PENNY;
		}

		min_coins_needed_to_make_change++;
	}
	printf("%i\n", min_coins_needed_to_make_change);

	return 0;
}
