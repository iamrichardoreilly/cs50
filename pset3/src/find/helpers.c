/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 *
 * Uses binary search.
 */
bool search(int value, int values[], int n)
{
	if (!n)
	{
		return false;
	}

	int min = 0, max = n - 1, mid;
	while (min <= max)
	{
		mid = (min + max)/2;

		if (values[mid] < value)
		{
			min = mid + 1;
		}
		else if (values[mid] == value)
		{
			return true;
		}
		else
		{
			max = mid - 1;
		}
	}

    return false;
}

/**
 * Sorts array of n values.
 *
 * Uses insertion sort.
 */
void sort(int values[], int n)
{
	if (!n)
	{
		return;
	}

	for (int i = 1; i <= n - 1; i++)
	{
		int j = i;
		while (j > 0 && values[j] < values[j - 1])
		{
			int tmp = values[j];
			values[j] = values[j - 1];
			values[j - 1] = tmp;

			j--;
		}
	}
}
