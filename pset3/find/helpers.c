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
 */
bool search(int value, int values[], int n)
{
	// boundaries of the searched zone
	int lower = 0;
	int upper = n - 1;

	// binary search
	while (lower <= upper)
	{
		// find the middle
		int middle = (lower + upper) / 2;

		if (values[middle] == value)
		{
			return true;
		}
		else if (values[middle] < value)
		{
			lower = middle + 1;
		}
		else if (values[middle] > value)
		{
			upper = middle - 1;
		}
	}

    // going through all the array without finding the value
    return false;
}

/**
 * Sorts array of n values using selection sort algorithm.
 */
void sort(int values[], int n)
{
	// iterate over the array 
	for (int i = 0; i < (n - 1); i++)
	{
		// smallest element and its position in sorted part
		int smallest = values[i];
		int position = i;

		// look through unsorted part of array
		for (int k = i + 1; k < n; k++)
		{	
			// find the next smallest element
			if (values[k] < smallest)
			{
				smallest = values[k];
				position = k;
			}
		}

		// swapping
		int temp = values[i];
		values[i] = smallest;
		values[position] = temp;
	}
    return;
}
